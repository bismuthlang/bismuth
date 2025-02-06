; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%Complex = type { %Integer, %Integer, %Integer }
%Integer = type { i32 }
%Color = type { i32, i32, i32 }

@0 = private unnamed_addr constant [19 x i8] c"Color: %u, %u, %u\0A\00", align 1
@1 = private unnamed_addr constant [21 x i8] c"Complex: %u, %u, %u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %x = alloca %Complex, align 8
  %1 = alloca %Complex, align 8
  %2 = alloca %Integer, align 8
  %3 = alloca %Integer, align 8
  %4 = alloca %Integer, align 8
  %z = alloca %Color, align 8
  %5 = alloca %Color, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %6 = getelementptr %Color, ptr %5, i32 0, i32 0
  store i32 25, ptr %6, align 4
  %7 = getelementptr %Color, ptr %5, i32 0, i32 1
  store i32 24, ptr %7, align 4
  %8 = getelementptr %Color, ptr %5, i32 0, i32 2
  store i32 23, ptr %8, align 4
  %9 = load %Color, ptr %5, align 4
  store %Color %9, ptr %z, align 4
  %10 = getelementptr %Color, ptr %z, i32 0, i32 0
  %11 = load i32, ptr %10, align 4
  %12 = getelementptr %Color, ptr %z, i32 0, i32 1
  %13 = load i32, ptr %12, align 4
  %14 = getelementptr %Color, ptr %z, i32 0, i32 2
  %15 = load i32, ptr %14, align 4
  %16 = call i32 (ptr, ...) @printf(ptr @0, i32 %11, i32 %13, i32 %15)
  %17 = getelementptr %Integer, ptr %4, i32 0, i32 0
  store i32 5, ptr %17, align 4
  %18 = load %Integer, ptr %4, align 4
  %19 = getelementptr %Integer, ptr %3, i32 0, i32 0
  store i32 4, ptr %19, align 4
  %20 = load %Integer, ptr %3, align 4
  %21 = getelementptr %Integer, ptr %2, i32 0, i32 0
  store i32 3, ptr %21, align 4
  %22 = load %Integer, ptr %2, align 4
  %23 = getelementptr %Complex, ptr %1, i32 0, i32 0
  store %Integer %18, ptr %23, align 4
  %24 = getelementptr %Complex, ptr %1, i32 0, i32 1
  store %Integer %20, ptr %24, align 4
  %25 = getelementptr %Complex, ptr %1, i32 0, i32 2
  store %Integer %22, ptr %25, align 4
  %26 = load %Complex, ptr %1, align 4
  store %Complex %26, ptr %x, align 4
  %27 = getelementptr %Complex, ptr %x, i32 0, i32 0, i32 0
  %28 = load i32, ptr %27, align 4
  %29 = getelementptr %Complex, ptr %x, i32 0, i32 1, i32 0
  %30 = load i32, ptr %29, align 4
  %31 = getelementptr %Complex, ptr %x, i32 0, i32 2, i32 0
  %32 = load i32, ptr %31, align 4
  %33 = call i32 (ptr, ...) @printf(ptr @1, i32 %28, i32 %30, i32 %32)
  %34 = call ptr @malloc(i32 4)
  store i32 0, ptr %34, align 4
  %35 = load ptr, ptr %c, align 8
  %36 = call %Unit @_WriteChannel(ptr %35, ptr %34)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
