#ifndef STATEMENT_H
#define STATEMENT_H

#include "../node.h"

namespace js {

class Statement: public Node
{
public:
    Statement();

    // Overrides
    void dump(int indent) override;
    inline std::string get_type() override { return "Statement"; };
};

} // namespace js

#endif // STATEMENT_H
