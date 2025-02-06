; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [18 x i8] c"a=%d, b=%d, c=%d\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  store i32 10, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %1 = mul nsw i32 2, %a1
  store i32 %1, ptr %b, align 4
  %b2 = load i32, ptr %b, align 4
  %a3 = load i32, ptr %a, align 4
  %2 = sdiv i32 %b2, %a3
  store i32 %2, ptr %c, align 4
  %a4 = load i32, ptr %a, align 4
  %b5 = load i32, ptr %b, align 4
  %c6 = load i32, ptr %c, align 4
  %3 = call i32 (...) @printf(ptr @0, i32 %a4, i32 %b5, i32 %c6)
  %4 = sub nsw i32 0, 1
  %5 = call ptr @malloc(i32 4)
  store i32 %4, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
