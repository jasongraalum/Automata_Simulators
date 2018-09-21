Machine_Name: TM_1 
Input_Alphabet: 0 1 #
Tape_Alphabet: 0 1 # x
States: q1 q2 q3 q4 q5 q6 q7 q8 qr qa
Start_State: q1
Accept_State: qa
Reject_State: qr
Transition_Table:
("x",R,q2) ("x",R,q3)  ("",R,q8)  ()        ()
("",R,q2)  ("",R,q2)   ("",R,q4)  ()        ()
("",R,q3)  ("",R,q3)   ("",R,q5)  ()        ()
("x",L,q6) ()          ()         ("",R,q4) ()
()         ("x",L,q6)  ()         ("",R,q5) ()
("",L,q6)  ("",L,q6)   ("",L,q7)  ("",L,q6) ()
("",L,q7)  ("",L,q7)   ()         ("",R,q1) ()
()         ()          ()         ("",R,q8) ("",R,qa)
