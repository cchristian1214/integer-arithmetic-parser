/*
    The following class definition
    defines a representation of a
    Token in an expression.
*/

class Token
{
public:
    //The token contains an enumeration representation expression types.
    enum Type
    {
        VALUE,
        OPERATOR,
        LPARENTHESIS,
        RPARENTHESIS
    };

    //A Constructor for VALUE types.
    Token(Type type, double value)
    {
        tokenType = type;
        tokenValue = value;
        tokenOperation = '$';
    }

    //A Constructor for OPERATOR types.
    Token(Type type, char op)
    {
        tokenType = type;
        tokenValue = 0;
        tokenOperation = op;
        if(op == '+' || op == '-') precedence = 1;
        else if(op == '*' || op == '/') precedence = 2;
    }

    //A Constructor for LPARENTHESIS and RPARENTHESIS types.
    Token(Type type)
    {
        tokenType = type;
        tokenValue = 0;
        tokenOperation = '$';
    }

    //Returns the type of the Token.
    Type type()
    {
        return tokenType;
    }

    //Returns the value of the Token.
    double value()
    {
        return tokenValue;
    }

    //Returns the operation of the Token.  
    char operation()
    {
        return tokenOperation;
    }

    //Returns the precedence of the operation associated with this Token.
    int operatorPrecedence()
    {
        return precedence;
    }

private:
    Type tokenType; //A Token's type.
    double tokenValue; //A Token's value.
    char tokenOperation; //A Token's operator.
    int precedence; //A Token's operator precedence.
};