; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [15 x i8] c"Prior to decl\0A\00", align 1
@1 = private unnamed_addr constant [12 x i8] c"Hey there!\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %io = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @0)
  %2 = call ptr @_Execute(ptr @"program::inner")
  store ptr %2, ptr %io, align 8
  %3 = call ptr @malloc(i32 8)
  store ptr @1, ptr %3, align 8
  %4 = load ptr, ptr %io, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = sub nsw i32 0, 1
  %7 = call ptr @malloc(i32 4)
  store i32 %6, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private %Unit @"program::inner"(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %s, align 8
  %s1 = load ptr, ptr %s, align 8
  %5 = call i32 (ptr, ...) @printf(ptr %s1)
  ret %Unit zeroinitializer
}

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
