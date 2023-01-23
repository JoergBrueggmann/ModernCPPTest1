/*******************************************************************************
    Each C++ expression is characterized by two independent properties:
        - a type and 
        - a value category.

    Each expression 
        - has some non-reference type, 
        - and each expression belongs to exactly one of the three 
            primary value categories:
            - prvalue, 
            - xvalue, and 
            - lvalue.

    A glvalue (“generalized” lvalue) is an expression whose evaluation 
        determines the identity of an object or function.

    A prvalue (“pure” rvalue) is an expression whose evaluation 
        - computes the value of an operand of a built-in operator 
            (such prvalue has no result object), or
        - initializes an object (such prvalue is said to have a result object).

    The result object may be a variable, an object created by new-expression, 
        a temporary created by temporary materialization, or a member thereof.

    NOTE: Non-void discarded expressions have a result object 
        (the materialized temporary); also, every class and array prvalue 
        has a result object except when it is the operand of decltype.

    An xvalue (an “eXpiring” value) is a glvalue that denotes an object 
        whose resources can be reused;
    an lvalue (so-called, historically, because lvalues could appear on 
        the left-hand side of an assignment expression) 
        is a glvalue that is not an xvalue;
    an rvalue (so-called, historically, because rvalues could appear on 
        the right-hand side of an assignment expression)
        is a prvalue or an xvalue.

    Source: https://en.cppreference.com/w/cpp/language/value_category
*/
