/*

    Stacks
        * bottom is always the oldest, top is always the newest
        * top is modified when inserting and removing
    
    When is a stack useful?
        * the undo feature of document editors, 
        * the redo feature would be a seperate stack.
    
    Program stack is also a good example
        * LIFO, last in first out 

    Implementation
        * Array List
            - append func can add values (could work as a stack insert (PUSH))
            - entries would be inserted in the last index of the array (top of the stack)
            - removing values -> free the data, decrease array size by 1 (POP)

            How do we access the top?
                - access [size - 1] (because of 0 indexing)

        * Linked List
            - TOP can be head or tail
            - PUSH - insert head, insert tail
            - POP - remove head, remove head
            - req. basic linked list...... (heat/tail, or circular, both need double links)
    


    Expression Parsing
        ex. 3 + (4 + 1 * 3) * 2

        infix exppression, has operators inbetween operands
        postfix expression (reverse polish notation), have operators after operands 
            ex. 3 4 +
            
        infix -     3 * 2 + 1
        postfix -   3 2 * 1 +

    2 steps for evaulating infix
        1. convert to postfix
        2. evaluate postfix

    Loop through expression
        If operant
            Push operand to stack  
        If operator
            operand 1 = top and pop
            operand 2 = top and pop
            push operand 2, operate with operand 1
            
        return top of stack
*/




