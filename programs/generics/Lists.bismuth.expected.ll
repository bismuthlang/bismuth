; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"program::LL2<int>" = type { i32, %"(Box<LL2<int>> + Empty)" }
%"(Box<LL2<int>> + Empty)" = type { i32, [8 x i8] }
%"Lists::LinkedList<boolean>" = type { %"(Box<LinkedList<boolean>> + Empty)", i1, %"(Empty + LinkedList<str> + boolean)", %"(Empty + LinkedList<str>)" }
%"(Box<LinkedList<boolean>> + Empty)" = type { i32, [8 x i8] }
%"(Empty + LinkedList<str> + boolean)" = type { i32, [1 x i8] }
%"(Empty + LinkedList<str>)" = type { i32, [0 x i8] }
%"Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32, %"(Empty + LinkedList<str> + int)", %"(Empty + LinkedList<str>)" }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"(Empty + LinkedList<str> + int)" = type { i32, [4 x i8] }

define %Unit @program(ptr %0) {
entry:
  %ll3 = alloca %"program::LL2<int>", align 8
  %ll2 = alloca %"Lists::LinkedList<boolean>", align 8
  %ll = alloca %"Lists::LinkedList<int>", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
