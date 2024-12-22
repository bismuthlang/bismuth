; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [18 x i8] c"WRONG! Got unit!\0A\00", align 1
@1 = private unnamed_addr constant [20 x i8] c"Correct if %u = 1!\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %other = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  %4 = call ptr @_Execute(ptr @c2)
  store ptr %4, ptr %other, align 8
  %5 = call ptr @malloc(i32 4)
  store i32 1, ptr %5, align 4
  %6 = load ptr, ptr %other, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = call ptr @malloc(i32 4)
  store i32 2, ptr %8, align 4
  %9 = load ptr, ptr %other, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %other, align 8
  %12 = call %Unit @_PreemptChannel(ptr %11, i32 1)
  ret %Unit zeroinitializer
}

define %Unit @c2(ptr %0) {
entry:
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %a = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLossyChannel(ptr %3)
  %5 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 1, ptr %5, align 4
  %6 = icmp ne ptr %4, null
  br i1 %6, label %val-opt, label %rest

val-opt:                                          ; preds = %entry
  store i32 2, ptr %5, align 4
  %7 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %8 = load i32, ptr %4, align 4
  store i32 %8, ptr %7, align 4
  br label %rest

rest:                                             ; preds = %val-opt, %entry
  %9 = load %"(Unit + int)", ptr %2, align 4
  %10 = call %Unit @free(ptr %4)
  store %"(Unit + int)" %9, ptr %a, align 4
  %a1 = load %"(Unit + int)", ptr %a, align 4
  store %"(Unit + int)" %a1, ptr %1, align 4
  %11 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %12 = load i32, ptr %11, align 4
  switch i32 %12, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %rest
  %13 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %14 = load %Unit, ptr %13, align 1
  store %Unit %14, ptr %u, align 1
  %15 = call i32 (ptr, ...) @printf(ptr @0)
  br label %match-cont

tagBranch2:                                       ; preds = %rest
  %16 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %17 = load i32, ptr %16, align 4
  store i32 %17, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %18 = call i32 (ptr, ...) @printf(ptr @1, i32 %i2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %rest
  %19 = load ptr, ptr %c, align 8
  %20 = call %Unit @_PreemptChannel(ptr %19, i32 1)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare %Unit @_PreemptChannel(ptr, i32)

declare ptr @_ReadLossyChannel(ptr)

declare %Unit @free(ptr)
