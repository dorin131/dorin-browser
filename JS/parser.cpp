#include "parser.h"

namespace js {

Parser::Parser(Tokenizer t)
    : tokenizer(t)
    , current_token(tokenizer.next_token())
    , peek_token(tokenizer.next_token())
{

}

void Parser::next_token()
{
    current_token = peek_token;
    peek_token = tokenizer.next_token();
}

bool Parser::current_token_is(Token::Type type)
{
    return current_token.get_type() == type;
}

bool Parser::peek_token_is(Token::Type type)
{
    return peek_token.get_type() == type;
}

Parser::Precedence Parser::current_precedence()
{
    if (precedences.find(current_token.get_type()) != precedences.end()) {
        return precedences.at(current_token.get_type());
    }
    return Precedence::LOWEST;
}

Parser::Precedence Parser::peek_precedence()
{
    if (precedences.find(peek_token.get_type()) != precedences.end()) {
        return precedences.at(peek_token.get_type());
    }
    return Precedence::LOWEST;
}

std::shared_ptr<Program> Parser::parse_program()
{
    auto program = std::make_shared<Program>();
    while (!current_token_is(Token::EOS)) {
        program->append(parse_statement());
        next_token();
    }
    return program;
}

std::shared_ptr<Statement> Parser::parse_statement()
{
    switch(current_token.get_type()) {
    case(Token::VAR):
        return parse_variable_statement();
    case(Token::IF):
        return parse_if_statement();
    case(Token::RETURN):
        return parse_return_statement();
    default:
        return parse_expression_statement();
    }
}

std::shared_ptr<ExpressionStatement> Parser::parse_expression_statement()
{
    return std::make_shared<ExpressionStatement>(parse_expression(Precedence::LOWEST));
}

std::shared_ptr<Node> Parser::parse_expression(Precedence precedence)
{
    std::shared_ptr<Node> left;

    switch(current_token.get_type()) {
    case(Token::NUMBER):
    case(Token::STRING):
        left = parse_literal_expression();
        break;
    case(Token::LPAREN):
        left = parse_grouped_expression();
        break;
    case(Token::IDENTIFIER):
        left = parse_identifier();
        break;
    case(Token::FUNCTION):
        left = parse_function_declaration();
        break;
    case(Token::LBRACE):
        left = parse_object_statement();
        break;
    default:
        throw SyntaxError("Unexpected token when parsing expression: " + current_token.get_value());
    }

    while(!peek_token_is(Token::SEMICOLON) && !peek_token_is(Token::COMMA) && precedence < peek_precedence()) {
        next_token();
        switch(current_token.get_type()) {
        case(Token::LPAREN):
            left = parse_call_expression(left);
            break;
        case(Token::ADD):
        case(Token::SUB):
        case(Token::DIV):
        case(Token::MUL):
        case(Token::EQ):
        case(Token::NE):
        case(Token::GT):
        case(Token::LT):
            left = parse_binary_expression(left);
            break;
        default:
            return left;
        }
    }

    if (peek_token_is(Token::SEMICOLON)) {
        next_token();
    }

    return left;
}

std::shared_ptr<Literal> Parser::parse_literal_expression()
{
    return std::make_shared<Literal>(current_token);
}

std::shared_ptr<BinaryExpression> Parser::parse_binary_expression(std::shared_ptr<Node> left)
{
    Token token = current_token;
    Precedence precedence = current_precedence();
    next_token();
    return std::make_shared<BinaryExpression>(token.get_value(), left, parse_expression(precedence));
}

std::shared_ptr<Node> Parser::parse_grouped_expression()
{
    next_token();
    auto expression = parse_expression(Precedence::LOWEST);

    if (!peek_token_is(Token::RPAREN)) {
        throw SyntaxError("Expected closing parenthesys");
    }
    next_token();
    return expression;
}

std::shared_ptr<VariableStatement> Parser::parse_variable_statement()
{
    next_token();
    if (!current_token_is(Token::IDENTIFIER)) {
        throw SyntaxError("Expecting identifier after \"var\" statement");
    }
    Token identifier = current_token;
    next_token();

    if (!current_token_is(Token::ASSIGN)) {
        throw SyntaxError("Expected variable value assignment");
    }
    next_token();
    std::shared_ptr<Node> expression = parse_expression(Precedence::LOWEST);

    return std::make_shared<VariableStatement>(Identifier(identifier), expression);
}

std::shared_ptr<FunctionDeclaration> Parser::parse_function_declaration()
{
    next_token();

    Identifier name;

    if (current_token_is(Token::IDENTIFIER)) {
        name = Identifier(current_token);
        next_token();
    }

    if (!current_token_is(Token::LPAREN)) {
        throw SyntaxError("Expected left paren after function declaration");
    }

    auto params = parse_function_parameters();

    if (!peek_token_is(Token::LBRACE)) {
        throw SyntaxError("Expected left brace");
    }
    next_token();
    auto body = parse_block_statement();

    return std::make_shared<FunctionDeclaration>(name, body, params);
}

std::list<Identifier> Parser::parse_function_parameters()
{
    std::list<Identifier> parameters;
    next_token();
    while (!current_token_is(Token::RPAREN)) {
        if (current_token_is(Token::IDENTIFIER)) {
            parameters.push_back(current_token);
        }
        next_token();
    }
    return parameters;
}

std::shared_ptr<BlockStatement> Parser::parse_block_statement()
{
    next_token();
    auto block_statement = std::make_shared<BlockStatement>();

    while (!current_token_is(Token::RBRACE)) {
        block_statement->append(parse_statement());
        next_token();
    }

    return block_statement;
}

std::shared_ptr<Expression> Parser::parse_identifier()
{
    if (peek_token_is(Token::PERIOD)) {
        return parse_object_expression();
    }
    return std::make_shared<Identifier>(current_token);
}

std::shared_ptr<ReturnStatement> Parser::parse_return_statement()
{
    next_token();

    auto return_statement = std::make_shared<ReturnStatement>(parse_expression(Precedence::LOWEST));

    if (peek_token_is(Token::SEMICOLON)) {
        next_token();
    }

    return return_statement;
}

std::shared_ptr<CallExpression> Parser::parse_call_expression(std::shared_ptr<Node> node)
{
    return std::make_shared<CallExpression>(node, parse_call_arguments());
}

std::vector<std::shared_ptr<Node>> Parser::parse_call_arguments()
{
    std::vector<std::shared_ptr<Node>> arguments;
    next_token();
    while(!current_token_is(Token::RPAREN)) {
        arguments.push_back(parse_expression(Precedence::LOWEST));
        if(peek_token_is(Token::COMMA)) next_token();
        next_token();
    }
    return arguments;
}

std::shared_ptr<ObjectStatement> Parser::parse_object_statement()
{
    auto obj = std::make_shared<ObjectStatement>();
    while(!peek_token_is(Token::RBRACE)) {
        expect_next_to_be(Token::IDENTIFIER, "Expected identifier");
        auto name = current_token;
        expect_next_to_be(Token::COLON, "Expected colon");
        next_token();
        auto expr = parse_expression(Precedence::LOWEST);
        obj->set(name, expr);
        if (peek_token_is(Token::COMMA)) next_token();
    }
    next_token();

    return obj;
}

std::shared_ptr<ObjectExpression> Parser::parse_object_expression()
{
    Identifier name = Identifier(current_token);
    std::list<Identifier> path;
    next_token();
    while (peek_token_is(Token::IDENTIFIER) || peek_token_is(Token::PERIOD)) {
        if (current_token_is(Token::PERIOD)) next_token();
        if (current_token_is(Token::IDENTIFIER)) {
            path.push_back(Identifier(current_token));
            if (peek_token_is(Token::PERIOD)) next_token();
        }
    }
    return std::make_shared<ObjectExpression>(name, path);
}

std::shared_ptr<IfStatement> Parser::parse_if_statement()
{
    return std::make_shared<IfStatement>();
}

void Parser::expect_next_to_be(Token::Type type, std::string msg)
{
    if (peek_token_is(type)) {
        next_token();
    } else {
        throw SyntaxError("Unexpected token: " + msg);
    }
}

} // namespace js
