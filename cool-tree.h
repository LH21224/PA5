#ifndef COOL_TREE_H
#define COOL_TREE_H

#include "tree.h"
#include "cool-tree.handcode.h"
#include <vector>

class Environment;

typedef class Program_class *Program;
class Program_class : public tree_node {
public:
   tree_node *copy() { return copy_Program(); }
   virtual Program copy_Program() = 0;
#ifdef Program_EXTRAS
   Program_EXTRAS
#endif
};

typedef class Class__class *Class_;
class Class__class : public tree_node {
public:
   tree_node *copy() { return copy_Class_(); }
   virtual Class_ copy_Class_() = 0;
#ifdef Class__EXTRAS
   Class__EXTRAS
#endif
};

typedef class Feature_class *Feature;
class Feature_class : public tree_node {
public:
   tree_node *copy() { return copy_Feature(); }
   virtual Feature copy_Feature() = 0;
   virtual bool IsMethod() = 0;
#ifdef Feature_EXTRAS
   Feature_EXTRAS
#endif
};

typedef class Formal_class *Formal;
class Formal_class : public tree_node {
public:
   tree_node *copy() { return copy_Formal(); }
   virtual Formal copy_Formal() = 0;
   virtual Symbol GetName() = 0;
#ifdef Formal_EXTRAS
   Formal_EXTRAS
#endif
};

typedef class Expression_class *Expression;
class Expression_class : public tree_node {
public:
   tree_node *copy() { return copy_Expression(); }
   virtual Expression copy_Expression() = 0;
   virtual bool IsEmpty() { return false; }
#ifdef Expression_EXTRAS
   Expression_EXTRAS
#endif
};

typedef class Case_class *Case;
class Case_class : public tree_node {
public:
   tree_node *copy() { return copy_Case(); }
   virtual Case copy_Case() = 0;
#ifdef Case_EXTRAS
   Case_EXTRAS
#endif
};

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

class program_class : public Program_class {
protected:
   Classes classes;
public:
   program_class(Classes a1) { classes = a1; }
   Program copy_Program();
   void dump(ostream& stream, int n);
   void cgen(ostream& os);
};

class class__class : public Class__class {
protected:
   Symbol name;
   Symbol parent;
   Features features;
   Symbol filename;
public:
   class__class(Symbol a1, Symbol a2, Features a3, Symbol a4) {
      name = a1; parent = a2; features = a3; filename = a4;
   }
   Class_ copy_Class_();
   void dump(ostream& stream, int n);
};

class method_class : public Feature_class {
public:
   Symbol name;
   Formals formals;
   Symbol return_type;
   Expression expr;
public:
   method_class(Symbol a1, Formals a2, Symbol a3, Expression a4) {
      name = a1; formals = a2; return_type = a3; expr = a4;
   }
   Feature copy_Feature();
   bool IsMethod() { return true; }
   void code(ostream& s, CgenNode* class_node);
   int GetArgNum() {
       int count = 0;
       for(int i = formals->first(); formals->more(i); i = formals->next(i)) count++;
       return count;
   }
   void dump(ostream& stream, int n);
};

class attr_class : public Feature_class {
public:
   Symbol name;
   Symbol type_decl;
   Expression init;
public:
   attr_class(Symbol a1, Symbol a2, Expression a3) {
      name = a1; type_decl = a2; init = a3;
   }
   Feature copy_Feature();
   bool IsMethod() { return false; }
   void dump(ostream& stream, int n);
};

class formal_class : public Formal_class {
protected:
   Symbol name;
   Symbol type_decl;
public:
   formal_class(Symbol a1, Symbol a2) { name = a1; type_decl = a2; }
   Formal copy_Formal();
   Symbol GetName() { return name; }
   void dump(ostream& stream, int n);
};

class branch_class : public Case_class {
public:
   Symbol name;
   Symbol type_decl;
   Expression expr;
public:
   branch_class(Symbol a1, Symbol a2, Expression a3) {
      name = a1; type_decl = a2; expr = a3;
   }
   Case copy_Case();
   void dump(ostream& stream, int n);
};

class assign_class : public Expression_class {
protected:
   Symbol name;
   Expression expr;
public:
   assign_class(Symbol a1, Expression a2) { name = a1; expr = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class static_dispatch_class : public Expression_class {
protected:
   Expression expr;
   Symbol type_name;
   Symbol name;
   Expressions actual;
public:
   static_dispatch_class(Expression a1, Symbol a2, Symbol a3, Expressions a4) {
      expr = a1; type_name = a2; name = a3; actual = a4;
   }
   Expression copy_Expression();
   std::vector<Expression> GetActuals() {
       std::vector<Expression> v;
       for(int i = actual->first(); actual->more(i); i = actual->next(i)) v.push_back(actual->nth(i));
       return v;
   }
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class dispatch_class : public Expression_class {
protected:
   Expression expr;
   Symbol name;
   Expressions actual;
public:
   dispatch_class(Expression a1, Symbol a2, Expressions a3) {
      expr = a1; name = a2; actual = a3;
   }
   Expression copy_Expression();
   std::vector<Expression> GetActuals() {
       std::vector<Expression> v;
       for(int i = actual->first(); actual->more(i); i = actual->next(i)) v.push_back(actual->nth(i));
       return v;
   }
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class cond_class : public Expression_class {
protected:
   Expression pred;
   Expression then_exp;
   Expression else_exp;
public:
   cond_class(Expression a1, Expression a2, Expression a3) {
      pred = a1; then_exp = a2; else_exp = a3;
   }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class loop_class : public Expression_class {
protected:
   Expression pred;
   Expression body;
public:
   loop_class(Expression a1, Expression a2) { pred = a1; body = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class typcase_class : public Expression_class {
protected:
   Expression expr;
   Cases cases;
public:
   typcase_class(Expression a1, Cases a2) { expr = a1; cases = a2; }
   Expression copy_Expression();
   std::vector<branch_class*> GetCases() {
       std::vector<branch_class*> v;
       for(int i = cases->first(); cases->more(i); i = cases->next(i)) v.push_back((branch_class*)cases->nth(i));
       return v;
   }
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class block_class : public Expression_class {
protected:
   Expressions body;
public:
   block_class(Expressions a1) { body = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class let_class : public Expression_class {
protected:
   Symbol identifier;
   Symbol type_decl;
   Expression init;
   Expression body;
public:
   let_class(Symbol a1, Symbol a2, Expression a3, Expression a4) {
      identifier = a1; type_decl = a2; init = a3; body = a4;
   }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class plus_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   plus_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class sub_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   sub_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class mul_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   mul_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class divide_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   divide_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class neg_class : public Expression_class {
protected:
   Expression e1;
public:
   neg_class(Expression a1) { e1 = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class lt_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   lt_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class eq_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   eq_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class leq_class : public Expression_class {
protected:
   Expression e1;
   Expression e2;
public:
   leq_class(Expression a1, Expression a2) { e1 = a1; e2 = a2; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class comp_class : public Expression_class {
protected:
   Expression e1;
public:
   comp_class(Expression a1) { e1 = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class int_const_class : public Expression_class {
protected:
   Symbol token;
public:
   int_const_class(Symbol a1) { token = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class bool_const_class : public Expression_class {
protected:
   Boolean val;
public:
   bool_const_class(Boolean a1) { val = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class string_const_class : public Expression_class {
protected:
   Symbol token;
public:
   string_const_class(Symbol a1) { token = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class new__class : public Expression_class {
protected:
   Symbol type_name;
public:
   new__class(Symbol a1) { type_name = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class isvoid_class : public Expression_class {
protected:
   Expression e1;
public:
   isvoid_class(Expression a1) { e1 = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class no_expr_class : public Expression_class {
public:
   no_expr_class() { }
   Expression copy_Expression();
   bool IsEmpty() { return true; }
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

class object_class : public Expression_class {
protected:
   Symbol name;
public:
   object_class(Symbol a1) { name = a1; }
   Expression copy_Expression();
   void dump(ostream& stream, int n);
   Expression_SHARED_EXTRAS
};

#endif
