; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"Foo<str>" = type { ptr, %"Bar<str>" }
%"Bar<str>" = type { ptr }
%"Optional<boolean>" = type { i32, [1 x i8] }
%"Optional<int>" = type { i32, [4 x i8] }

define %Unit @program(ptr %0) {
entry:
  %foo = alloca %"Foo<str>", align 8
  %optBool = alloca %"Optional<boolean>", align 8
  %optInt = alloca %"Optional<int>", align 8
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
