; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"Main 1!\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"Main 2!\0A\00", align 1

define ptr @getMain1() {
entry:
  ret ptr @"getMain1::main"
}

define ptr @getMain2() {
entry:
  ret ptr @"getMain2::main"
}

define %Unit @program(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @getMain1()
  %2 = call i32 %1()
  %3 = call ptr @getMain2()
  %4 = call i32 %3()
  %5 = add nsw i32 %2, %4
  %6 = call ptr @malloc(i32 4)
  store i32 %5, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private i32 @"getMain1::main"() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0)
  ret i32 1
}

define private i32 @"getMain2::main"() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @1)
  ret i32 2
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
