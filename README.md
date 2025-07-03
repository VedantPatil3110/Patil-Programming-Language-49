🚀 Patil Programming Language 49 (PPL49) Showcase
Welcome to PPL49! Below is a complete list of features with example commands and expected outputs. Run each command using the interactive shell (>>> prompt).

✅ 1. Basic Printing & Strings
text
Copy
Edit
>>> set_str greet "Hello, "
>>> set_str name "Vedant"
>>> concat_str welcome greet name
>>> print welcome
Hello, Vedant

✅ 2. BFS & DFS on Integer Graphs
text
Copy
Edit
>>> add_edge g1 1 2
>>> add_edge g1 1 3
>>> add_edge g1 2 4
>>> add_edge g1 3 5
>>> add_edge g1 4 6
>>> bfs g1 1
1 2 3 4 5 6
>>> dfs g1 1
1 2 4 6 3 5

✅ 3. BFS & DFS on String Graphs
text
Copy
Edit
>>> add_edge_str sg1 A B
>>> add_edge_str sg1 A C
>>> add_edge_str sg1 B D
>>> add_edge_str sg1 C E
>>> add_edge_str sg1 D F
>>> bfs_str sg1 A
A B C D E F
>>> dfs_str sg1 A
A B D F C E

✅ 4. Dijkstra (Integer Weighted Graph)
text
Copy
Edit
>>> add_weighted_edge wg1 1 2 4
>>> add_weighted_edge wg1 1 3 1
>>> add_weighted_edge wg1 3 2 2
>>> add_weighted_edge wg1 2 4 1
>>> add_weighted_edge wg1 3 4 5
>>> dijkstra wg1 1
Distance to 1 = 0
Distance to 2 = 3
Distance to 3 = 1
Distance to 4 = 4

✅ 5. Dijkstra (String Unweighted via BFS)
text
Copy
Edit
>>> add_edge_str sg1 A B
>>> add_edge_str sg1 A C
>>> add_edge_str sg1 B D
>>> add_edge_str sg1 C D
>>> add_edge_str sg1 D E
>>> dijkstra_str sg1 A
Distance to A = 0
Distance to B = 1
Distance to C = 1
Distance to D = 2
Distance to E = 3

✅ 6. Map
text
Copy
Edit
>>> put_map mymap key1 100
>>> put_map mymap key2 200
>>> print_map mymap
key1: 100
key2: 200

✅ 7. Set
text
Copy
Edit
>>> add_to_set myset 5
>>> add_to_set myset 10
>>> add_to_set myset 5  // duplicate ignored
>>> print_set myset
5 10

✅ 8. Max Priority Queue
text
Copy
Edit
>>> push_pq pq1 30
>>> push_pq pq1 10
>>> push_pq pq1 20
>>> peek_pq pq1
30
>>> size_pq pq1
3
>>> pop_pq pq1
>>> peek_pq pq1
20

✅ 9. Min Priority Queue
text
Copy
Edit
>>> push_min_pq mpq1 30
>>> push_min_pq mpq1 10
>>> push_min_pq mpq1 20
>>> peek_min_pq mpq1
10
>>> pop_min_pq mpq1
>>> peek_min_pq mpq1
20

✅ 10. Tree Operations
text
Copy
Edit
>>> create_tree t1
>>> insert_tree t1 5
>>> insert_tree t1 3
>>> insert_tree t1 7
>>> insert_tree t1 1
>>> insert_tree t1 4
>>> bfs_tree t1
5 3 7 1 4
>>> dfs_tree t1
5 3 1 4 7
>>> inorder t1
1 3 4 5 7
>>> preorder t1
5 3 1 4 7
>>> postorder t1
1 4 3 7 5
>>> height t1
3
>>> delete_tree t1 7
>>> inorder t1
1 3 4 5
>>> search_tree t1 7
Not Found

✅ 11. Array Operations
text
Copy
Edit
>>> set_arr arr1 4 2 5 1 3
>>> print arr1
4 2 5 1 3
>>> sort_array arr1
>>> print arr1
1 2 3 4 5
>>> sort_array_desc arr1
>>> print arr1
5 4 3 2 1
>>> reverse_array arr1
>>> print arr1
1 2 3 4 5
>>> rotate_array arr1 2
>>> print arr1
3 4 5 1 2
>>> rotate_array arr1 -1
>>> print arr1
2 3 4 5 1

✅ 12. Stack
text
Copy
Edit
>>> push_stack s1 10
>>> push_stack s1 20
>>> push_stack s1 30
>>> print s1
30 20 10
>>> pop_stack s1
>>> peek_stack s1
20
>>> size_stack s1
2
>>> empty_stack s1
false

✅ 13. Linked List
text
Copy
Edit
>>> add_front l1 5
>>> add_front l1 10
>>> add_front l1 15
>>> add_end l1 20
>>> add_end l1 25
>>> print l1
15 10 5 20 25

>>> add_end ll1 10
>>> add_end ll1 20
>>> add_end ll1 30
>>> print ll1
10 20 30

>>> search_linkedlist ll1 20
Found at position 1
>>> search_linkedlist ll1 99
Not found

>>> reverse_linkedlist ll1
>>> print ll1
30 20 10
>>> rotate_linkedlist ll1 2
>>> print ll1
10 30 20

✅ 14. String Functions
text
Copy
Edit
>>> set_str s1 "hello"
>>> print s1
hello
>>> reverse_string s1
>>> print s1
olleh
>>> rotate_string s1 2
>>> print s1
eholl
>>> rotate_string s1 -1
>>> print s1
holle

✅ 15. OOP Features (Classes, Cloning, Inheritance)
text
Copy
Edit
>>> class Person
>>> set_attr Person name "Vedant"
>>> set_attr Person greet "Hello, {0}!"
>>> call_method Person greet Vedant
Hello, Vedant!

>>> clone_class Student Person
>>> print_class Student
name: Vedant
greet: Hello, {0}!

>>> class Base
>>> set_attr Base attr "base_value"
>>> class Derived
>>> inherit_class Derived Base
>>> print_class Derived
attr: base_value

>>> delete_attr Derived attr
Deleted attribute 'attr' from 'Derived'

✅ 16. Print Graph Structure (Verification)
text
Copy
Edit
>>> print_graph g1
1: 2 3
2: 4
3: 5
4: 6
5:
6:

>>> print_graph_str sg1
A: B C
B: D
C: E
D: F
E:
F:

✅ 17. Error Handling Examples
text
Copy
Edit
>>> get_map mymap keyX
0

>>> search_linkedlist emptylist 10
[Linked List 'emptylist' not found]

>>> rotate_linkedlist ll1 100
>>> print ll1
30 20 10
