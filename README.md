# `12balls`

my solution to the 12 balls problem

Currently my solution requires 4 compares (we need 3 compares for a full solution)

## How my 'solution' works

Divide the 12 balls into 3 groups. (we will call the groups G<sub>0</sub>, G<sub>1</sub>, and G<sub>2</sub>)

Have an extra group named S, and a variable named W.

Now, compare G<sub>0</sub> and G<sub>1</sub>. Store the result in R<sub>0</sub>.

Then, compare G<sub>0</sub> and G<sub>2</sub>. Store the result in R<sub>1</sub>. 

If R<sub>0</sub> is `=`, set S to G<sub>2</sub> and set W to 0 if R<sub>1</sub> is `>` and 1 if R<sub>1</sub> is `<`.

If R<sub>1</sub> is `=`, set S to G<sub>1</sub> and set W to 0 if R<sub>0</sub> is `>` and 1 if R<sub>0</sub> is `<`.

If R<sub>0</sub> and R<sub>1</sub> are the same, set S to G<sub>0</sub> and set W to 0 if R<sub>0</sub> is `>` and 1 if R<sub>0</sub> is `<`.

