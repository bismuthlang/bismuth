; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%Value = type { i32 }

@0 = private unnamed_addr constant [4 x i8] c"25\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"16\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"20\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"72\0A\00", align 1
@4 = private unnamed_addr constant [4 x i8] c"50\0A\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"57\0A\00", align 1

define %Unit @Database(ptr %0) {
entry:
  %val = alloca %Value, align 8
  %key = alloca i32, align 4
  %k = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call i1 @_ShouldLinearLoop(ptr %1)
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %3 = load ptr, ptr %c, align 8
  %4 = call i32 @_ReadLinearProjection(ptr %3)
  switch i32 %4, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop
  %5 = call i32 (ptr, ...) @printf(ptr @0)
  %6 = load ptr, ptr %c, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load i32, ptr %7, align 4
  %9 = call %Unit @free(ptr %7)
  store i32 %8, ptr %k, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %loop
  %10 = call i32 (ptr, ...) @printf(ptr @1)
  %11 = load ptr, ptr %c, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i32, ptr %12, align 4
  %14 = call %Unit @free(ptr %12)
  %15 = call ptr @malloc(i32 4)
  store i32 %13, ptr %15, align 4
  %16 = load ptr, ptr %c, align 8
  %17 = call %Unit @_WriteChannel(ptr %16, ptr %15)
  br label %match-cont

tagBranch3:                                       ; preds = %loop
  %18 = call i32 (ptr, ...) @printf(ptr @2)
  %19 = load ptr, ptr %c, align 8
  %20 = call ptr @_ReadLinearChannel(ptr %19)
  %21 = load i32, ptr %20, align 4
  %22 = call %Unit @free(ptr %20)
  store i32 %21, ptr %key, align 4
  %23 = load ptr, ptr %c, align 8
  %24 = call ptr @_ReadLinearChannel(ptr %23)
  %25 = load %Value, ptr %24, align 4
  %26 = call %Unit @free(ptr %24)
  store %Value %25, ptr %val, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %tagBranch2, %tagBranch1, %loop
  %27 = load ptr, ptr %c, align 8
  %28 = call i1 @_ShouldLinearLoop(ptr %27)
  br i1 %28, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %a = alloca i32, align 4
  %setRq = alloca ptr, align 8
  %rqs = alloca ptr, align 8
  %db = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @Database)
  store ptr %1, ptr %db, align 8
  %2 = call ptr @_Execute(ptr @requests)
  store ptr %2, ptr %rqs, align 8
  %3 = call ptr @_Execute(ptr @writeRequest)
  store ptr %3, ptr %setRq, align 8
  %4 = load ptr, ptr %setRq, align 8
  %5 = call i1 @_ShouldLinearLoop(ptr %4)
  br i1 %5, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %6 = load ptr, ptr %db, align 8
  %7 = call %Unit @_ContractChannel(ptr %6)
  %8 = load ptr, ptr %db, align 8
  %9 = call %Unit @_WriteProjection(ptr %8, i32 3)
  %10 = load ptr, ptr %setRq, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load i32, ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  %14 = call ptr @malloc(i32 4)
  store i32 %12, ptr %14, align 4
  %15 = load ptr, ptr %db, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  %17 = load ptr, ptr %setRq, align 8
  %18 = call ptr @_ReadLinearChannel(ptr %17)
  %19 = load %Value, ptr %18, align 4
  %20 = call %Unit @free(ptr %18)
  %21 = call ptr @malloc(i32 4)
  store %Value %19, ptr %21, align 4
  %22 = load ptr, ptr %db, align 8
  %23 = call %Unit @_WriteChannel(ptr %22, ptr %21)
  %24 = load ptr, ptr %setRq, align 8
  %25 = call i1 @_ShouldLinearLoop(ptr %24)
  br i1 %25, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %26 = load ptr, ptr %rqs, align 8
  %27 = call i1 @_ShouldLinearLoop(ptr %26)
  br i1 %27, label %loop1, label %rest3

loop1:                                            ; preds = %match-cont, %rest
  %28 = load ptr, ptr %db, align 8
  %29 = call %Unit @_ContractChannel(ptr %28)
  %30 = load ptr, ptr %rqs, align 8
  %31 = call i32 @_ReadLinearProjection(ptr %30)
  switch i32 %31, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop1
  %32 = call i32 (ptr, ...) @printf(ptr @3)
  %33 = load ptr, ptr %db, align 8
  %34 = call %Unit @_WriteProjection(ptr %33, i32 1)
  %35 = load ptr, ptr %rqs, align 8
  %36 = call ptr @_ReadLinearChannel(ptr %35)
  %37 = load i32, ptr %36, align 4
  %38 = call %Unit @free(ptr %36)
  %39 = call ptr @malloc(i32 4)
  store i32 %37, ptr %39, align 4
  %40 = load ptr, ptr %db, align 8
  %41 = call %Unit @_WriteChannel(ptr %40, ptr %39)
  br label %match-cont

tagBranch2:                                       ; preds = %loop1
  %42 = call i32 (ptr, ...) @printf(ptr @4)
  %43 = load ptr, ptr %db, align 8
  %44 = call %Unit @_WriteProjection(ptr %43, i32 2)
  %45 = load ptr, ptr %rqs, align 8
  %46 = call ptr @_ReadLinearChannel(ptr %45)
  %47 = load i32, ptr %46, align 4
  %48 = call %Unit @free(ptr %46)
  %49 = call ptr @malloc(i32 4)
  store i32 %47, ptr %49, align 4
  %50 = load ptr, ptr %db, align 8
  %51 = call %Unit @_WriteChannel(ptr %50, ptr %49)
  %52 = load ptr, ptr %db, align 8
  %53 = call ptr @_ReadLinearChannel(ptr %52)
  %54 = load i32, ptr %53, align 4
  %55 = call %Unit @free(ptr %53)
  store i32 %54, ptr %a, align 4
  %a2 = load i32, ptr %a, align 4
  %56 = call ptr @malloc(i32 4)
  store i32 %a2, ptr %56, align 4
  %57 = load ptr, ptr %rqs, align 8
  %58 = call %Unit @_WriteChannel(ptr %57, ptr %56)
  br label %match-cont

tagBranch3:                                       ; preds = %loop1
  %59 = call i32 (ptr, ...) @printf(ptr @5)
  %60 = load ptr, ptr %db, align 8
  %61 = call %Unit @_WriteProjection(ptr %60, i32 3)
  %62 = load ptr, ptr %rqs, align 8
  %63 = call ptr @_ReadLinearChannel(ptr %62)
  %64 = load i32, ptr %63, align 4
  %65 = call %Unit @free(ptr %63)
  %66 = call ptr @malloc(i32 4)
  store i32 %64, ptr %66, align 4
  %67 = load ptr, ptr %db, align 8
  %68 = call %Unit @_WriteChannel(ptr %67, ptr %66)
  %69 = load ptr, ptr %rqs, align 8
  %70 = call ptr @_ReadLinearChannel(ptr %69)
  %71 = load %Value, ptr %70, align 4
  %72 = call %Unit @free(ptr %70)
  %73 = call ptr @malloc(i32 4)
  store %Value %71, ptr %73, align 4
  %74 = load ptr, ptr %db, align 8
  %75 = call %Unit @_WriteChannel(ptr %74, ptr %73)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %tagBranch2, %tagBranch1, %loop1
  %76 = load ptr, ptr %rqs, align 8
  %77 = call i1 @_ShouldLinearLoop(ptr %76)
  br i1 %77, label %loop1, label %rest3

rest3:                                            ; preds = %match-cont, %rest
  %78 = load ptr, ptr %db, align 8
  %79 = call %Unit @_WeakenChannel(ptr %78)
  %80 = call ptr @malloc(i32 4)
  store i32 0, ptr %80, align 4
  %81 = load ptr, ptr %c, align 8
  %82 = call %Unit @_WriteChannel(ptr %81, ptr %80)
  ret %Unit zeroinitializer
}

define %Unit @requests(ptr %0) {
entry:
  %opt = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call %Unit @_ContractChannel(ptr %1)
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteProjection(ptr %3, i32 2)
  %5 = call ptr @malloc(i32 4)
  store i32 0, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %c, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  store i32 %10, ptr %opt, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WeakenChannel(ptr %12)
  ret %Unit zeroinitializer
}

define %Unit @writeRequest(ptr %0) {
entry:
  %1 = alloca %Value, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_ContractChannel(ptr %2)
  %4 = call ptr @malloc(i32 4)
  store i32 4, ptr %4, align 4
  %5 = load ptr, ptr %c, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %7 = getelementptr %Value, ptr %1, i32 0, i32 0
  store i32 2, ptr %7, align 4
  %8 = load %Value, ptr %1, align 4
  %9 = call ptr @malloc(i32 4)
  store %Value %8, ptr %9, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call %Unit @_WriteChannel(ptr %10, ptr %9)
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WeakenChannel(ptr %12)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare i1 @_ShouldLinearLoop(ptr)

declare i32 @_ReadLinearProjection(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WriteProjection(ptr, i32)

declare %Unit @_WeakenChannel(ptr)
