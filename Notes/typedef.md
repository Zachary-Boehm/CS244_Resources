A typedef declaration may declare one or many identifiers on the same line (e.g. int and a pointer to int), it may declare array and function types, pointers and references, class types, etc. Every identifier introduced in this declaration becomes a typedef-name, which is a synonym for the type of the object or function that it would become if the keyword typedef were removed.

The typedef specifier cannot be combined with any other specifier except for type-specifiers.

The typedef-names are aliases for existing types, and are not declarations of new types. Typedef cannot be used to change the meaning of an existing type name (including a typedef-name). Once declared, a typedef-name may only be redeclared to refer to the same type again. Typedef names are only in effect in the scope where they are visible: different functions or class declarations may define identically-named types with different meaning. 

**Example**
![example](/Notes/Example.png)
