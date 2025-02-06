; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [10 x i8] c"LAM: %u:\0A\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"ref(1) = %u\0A\00", align 1
@2 = private unnamed_addr constant [10 x i8] c"LAM2: %u\0A\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"ref(1) = %u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %ref = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"program::#lambda", ptr %ref, align 8
  %ref1 = load ptr, ptr %ref, align 8
  %1 = call i32 %ref1(i32 10)
  %ref2 = load ptr, ptr %ref, align 8
  %2 = call i32 %ref2(i32 1)
  %3 = call i32 (...) @printf(ptr @1, i32 %2)
  store ptr @"program::#lambda.0", ptr %ref, align 8
  %ref3 = load ptr, ptr %ref, align 8
  %4 = call i32 %ref3(i32 10)
  %ref4 = load ptr, ptr %ref, align 8
  %5 = call i32 %ref4(i32 1)
  %6 = call i32 (...) @printf(ptr @3, i32 %5)
  %7 = call ptr @malloc(i32 4)
  store i32 0, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

define private i32 @"program::#lambda"(i32 %0) {
entry:
  %x = alloca i32, align 4
  store i32 %0, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %1 = call i32 (...) @printf(ptr @0, i32 %x1)
  %x2 = load i32, ptr %x, align 4
  ret i32 %x2
}

define private i32 @"program::#lambda.0"(i32 %0) {
entry:
  %z = alloca i32, align 4
  store i32 %0, ptr %z, align 4
  %z1 = load i32, ptr %z, align 4
  %1 = call i32 (...) @printf(ptr @2, i32 %z1)
  %z2 = load i32, ptr %z, align 4
  ret i32 %z2
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
