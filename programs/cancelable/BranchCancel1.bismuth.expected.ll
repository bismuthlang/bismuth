; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }
%"(Unit + boolean)" = type { i32, [1 x i8] }

@0 = private unnamed_addr constant [7 x i8] c"Error!\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @c2(ptr %0) {
entry:
  %b.0 = alloca %"(Unit + int)", align 8
  %1 = alloca %"(Unit + int)", align 8
  %a = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %b = alloca %"(Unit + boolean)", align 8
  %3 = alloca %"(Unit + boolean)", align 8
  %i = alloca i32, align 4
  %a.0 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call i32 @_ReadLossyProjection(ptr %5)
  switch i32 %6, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 0, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %entry
  %7 = call ptr @malloc(i32 4)
  store i32 0, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %10 = load ptr, ptr %c, align 8
  %11 = call ptr @_ReadLossyChannel(ptr %10)
  %12 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 1, ptr %12, align 4
  %13 = icmp ne ptr %11, null
  br i1 %13, label %val-opt, label %rest

val-opt:                                          ; preds = %tagBranch2
  store i32 2, ptr %12, align 4
  %14 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  %15 = load i32, ptr %11, align 4
  store i32 %15, ptr %14, align 4
  br label %rest

rest:                                             ; preds = %val-opt, %tagBranch2
  %16 = load %"(Unit + int)", ptr %4, align 4
  %17 = call %Unit @free(ptr %11)
  store %"(Unit + int)" %16, ptr %a.0, align 4
  br label %match-cont

tagBranch3:                                       ; preds = %entry
  %18 = call i32 (ptr, ...) @printf(ptr @0)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %rest, %tagBranch1, %entry
  store i32 0, ptr %i, align 4
  %19 = load ptr, ptr %c, align 8
  %20 = call %Unit @_PreemptChannel(ptr %19, i32 1)
  %i1 = load i32, ptr %i, align 4
  %21 = icmp slt i32 %i1, 10
  br i1 %21, label %loop, label %rest6

loop:                                             ; preds = %rest3, %match-cont
  %22 = load ptr, ptr %c, align 8
  %23 = call %Unit @_ContractChannel(ptr %22)
  %24 = load ptr, ptr %c, align 8
  %25 = call ptr @_ReadLossyChannel(ptr %24)
  %26 = getelementptr %"(Unit + boolean)", ptr %3, i32 0, i32 0
  store i32 1, ptr %26, align 4
  %27 = icmp ne ptr %25, null
  br i1 %27, label %val-opt2, label %rest3

val-opt2:                                         ; preds = %loop
  store i32 2, ptr %26, align 4
  %28 = getelementptr %"(Unit + boolean)", ptr %3, i32 0, i32 1
  %29 = load i1, ptr %25, align 1
  store i1 %29, ptr %28, align 1
  br label %rest3

rest3:                                            ; preds = %val-opt2, %loop
  %30 = load %"(Unit + boolean)", ptr %3, align 4
  %31 = call %Unit @free(ptr %25)
  store %"(Unit + boolean)" %30, ptr %b, align 4
  %i4 = load i32, ptr %i, align 4
  %32 = add nsw i32 %i4, 1
  store i32 %32, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %33 = icmp slt i32 %i5, 10
  br i1 %33, label %loop, label %rest6

rest6:                                            ; preds = %rest3, %match-cont
  %34 = load ptr, ptr %c, align 8
  %35 = call %Unit @_WeakenChannel(ptr %34)
  %36 = load ptr, ptr %c, align 8
  %37 = call %Unit @_PreemptChannel(ptr %36, i32 2)
  %38 = load ptr, ptr %c, align 8
  %39 = call ptr @_ReadLossyChannel(ptr %38)
  %40 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 1, ptr %40, align 4
  %41 = icmp ne ptr %39, null
  br i1 %41, label %val-opt7, label %rest8

val-opt7:                                         ; preds = %rest6
  store i32 2, ptr %40, align 4
  %42 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %43 = load i32, ptr %39, align 4
  store i32 %43, ptr %42, align 4
  br label %rest8

rest8:                                            ; preds = %val-opt7, %rest6
  %44 = load %"(Unit + int)", ptr %2, align 4
  %45 = call %Unit @free(ptr %39)
  store %"(Unit + int)" %44, ptr %a, align 4
  %46 = call ptr @malloc(i32 4)
  store i32 2, ptr %46, align 4
  %47 = load ptr, ptr %c, align 8
  %48 = call %Unit @_WriteChannel(ptr %47, ptr %46)
  %49 = load ptr, ptr %c, align 8
  %50 = call ptr @_ReadLossyChannel(ptr %49)
  %51 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  store i32 1, ptr %51, align 4
  %52 = icmp ne ptr %50, null
  br i1 %52, label %val-opt9, label %rest10

val-opt9:                                         ; preds = %rest8
  store i32 2, ptr %51, align 4
  %53 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %54 = load i32, ptr %50, align 4
  store i32 %54, ptr %53, align 4
  br label %rest10

rest10:                                           ; preds = %val-opt9, %rest8
  %55 = load %"(Unit + int)", ptr %1, align 4
  %56 = call %Unit @free(ptr %50)
  store %"(Unit + int)" %55, ptr %b.0, align 4
  %57 = load ptr, ptr %c, align 8
  %58 = call %Unit @_PreemptChannel(ptr %57, i32 3)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare i32 @_ReadLossyProjection(ptr)

declare ptr @_ReadLossyChannel(ptr)

declare %Unit @free(ptr)

declare %Unit @_PreemptChannel(ptr, i32)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WeakenChannel(ptr)
