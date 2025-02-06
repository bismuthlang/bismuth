; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [17 x i8] c"Heap size = %ld\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %b = alloca ptr, align 8
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %i1 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %i1, 10000000
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %i2 = load i32, ptr %i, align 4
  %2 = call ptr @GC_malloc(i64 4)
  store i32 %i2, ptr %2, align 4
  %3 = call ptr @GC_malloc(i64 8)
  store ptr %2, ptr %3, align 8
  store ptr %3, ptr %b, align 8
  %4 = call i32 @GC_get_heap_size()
  %5 = call %Unit (ptr, ...) @printf(ptr @0, i32 %4)
  %i3 = load i32, ptr %i, align 4
  %6 = add nsw i32 %i3, 1
  store i32 %6, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %7 = icmp slt i32 %i4, 10000000
  br i1 %7, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %8 = call ptr @malloc(i32 4)
  store i32 0, ptr %8, align 4
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare i32 @GC_get_heap_size()

declare ptr @GC_malloc(i64)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
