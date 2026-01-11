class Node {
    value : Int;
    left  : Node;
    right : Node;

    init(v : Int) : Node {
        {
            value <- v;
            self;
        }
    };

    setLeft(l : Node) : Node {
        {
            left <- l;
            self;
        }
    };

    setRight(r : Node) : Node {
        {
            right <- r;
            self;
        }
    };

    inorder(io : IO) : Object {
        {
            if (isvoid left) then 0 else left.inorder(io) fi;
            io.out_int(value);
            io.out_string(" ");
            if (isvoid right) then 0 else right.inorder(io) fi;
            self;
        }
    };
};

class Main inherits IO {
    main() : Object {
        let
            root : Node <- (new Node).init(1),  (* 这里要逗号 *)
            n2   : Node <- (new Node).init(2),  (* 这里要逗号 *)
            n3   : Node <- (new Node).init(3),  (* 这里要逗号 *)
            n4   : Node <- (new Node).init(4)   (* 最后一个变量后面绝对不能有逗号 *)
        in
            {
                root.setLeft(n2);
                root.setRight(n3);
                n2.setLeft(n4);
                root.inorder(self);
                out_string("\n");
                self;
            }
    };
};
