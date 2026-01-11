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
            if (isvoid right) then 0 else right.inorder(io) fi;
            self;
        }
    };
};

class Main inherits IO {
    main() : Object {
        let
            root : Node <- new Node.init(1),
            n2   : Node <- new Node.init(2),
            n3   : Node <- new Node.init(3),
            n4   : Node <- new Node.init(4)
        in
            {
                root.setLeft(n2);
                root.setRight(n3);
                n2.setLeft(n4);
                root.inorder(self); 
                self;
            }
    };
};
