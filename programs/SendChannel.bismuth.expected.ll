; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %temp = alloca i32, align 4
  %foo1 = alloca ptr, align 8
  %foo2 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @Foo2)
  store ptr %1, ptr %foo2, align 8
  %2 = call ptr @_Execute(ptr @Foo1)
  store ptr %2, ptr %foo1, align 8
  %foo11 = load ptr, ptr %foo1, align 8
  %3 = call ptr @malloc(i32 8)
  store ptr %foo11, ptr %3, align 8
  %4 = load ptr, ptr %foo2, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %foo2, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load i32, ptr %7, align 4
  %9 = call %Unit @free(ptr %7)
  store i32 %8, ptr %temp, align 4
  %temp2 = load i32, ptr %temp, align 4
  %10 = call ptr @malloc(i32 4)
  store i32 %temp2, ptr %10, align 4
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  ret %Unit zeroinitializer
}

define %Unit @Foo1(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 5, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @Foo2(ptr %0) {
entry:
  %c2 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %c2, align 8
  %5 = load ptr, ptr %c2, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load i32, ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  %9 = call ptr @malloc(i32 4)
  store i32 %7, ptr %9, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call %Unit @_WriteChannel(ptr %10, ptr %9)
  ret %Unit zeroinitializer
}

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
