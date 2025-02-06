; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + Value)" = type { i32, [4 x i8] }
%Value = type { i32 }

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [4 x i8] c"*, \00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@3 = private unnamed_addr constant [25 x i8] c"Initial Database State:\0A\00", align 1
@4 = private unnamed_addr constant [20 x i8] c"Database Updated: \0A\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"72\0A\00", align 1
@6 = private unnamed_addr constant [25 x i8] c"Read Request for 4 got: \00", align 1
@7 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@8 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@9 = private unnamed_addr constant [26 x i8] c"Read Request for 20 got: \00", align 1
@10 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@11 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define %Unit @Database(ptr %0) {
entry:
  %k = alloca i32, align 4
  %1 = alloca %"(Unit + Value)", align 8
  %2 = alloca %"(Unit + Value)", align 8
  %data = alloca [10 x %Value], align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = call i32 (ptr, ...) @printf(ptr @3)
  %data1 = load [10 x %Value], ptr %data, align 4
  %4 = call %Unit @"Database::PrintDatabase"([10 x %Value] %data1)
  %5 = load ptr, ptr %c, align 8
  %6 = call i1 @_ShouldLinearLoop(ptr %5)
  br i1 %6, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %7 = load ptr, ptr %c, align 8
  %8 = call i32 @_ReadLinearProjection(ptr %7)
  switch i32 %8, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop
  %9 = load ptr, ptr %c, align 8
  %10 = call ptr @_ReadLinearChannel(ptr %9)
  %11 = load i32, ptr %10, align 4
  %12 = call %Unit @free(ptr %10)
  %13 = icmp slt i32 %11, 10
  br i1 %13, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %tagBranch1
  %14 = icmp sge i32 %11, 0
  br i1 %14, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %15 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %11
  %16 = load %Value, ptr %15, align 4
  %17 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 0
  store i32 2, ptr %17, align 4
  %18 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  store %Value %16, ptr %18, align 4
  %19 = load %"(Unit + Value)", ptr %2, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %tagBranch1
  %20 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 0
  store i32 1, ptr %20, align 4
  %21 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  store %Unit zeroinitializer, ptr %21, align 1
  %22 = load %"(Unit + Value)", ptr %1, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + Value)" [ %19, %accessGTZ ], [ %22, %accessBad ]
  %23 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %arrayAccess, ptr %23, align 4
  %24 = load ptr, ptr %c, align 8
  %25 = call %Unit @_WriteChannel(ptr %24, ptr %23)
  br label %match-cont

tagBranch2:                                       ; preds = %loop
  %26 = load ptr, ptr %c, align 8
  %27 = call ptr @_ReadLinearChannel(ptr %26)
  %28 = load i32, ptr %27, align 4
  %29 = call %Unit @free(ptr %27)
  %30 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %28
  %31 = load ptr, ptr %c, align 8
  %32 = call ptr @_ReadLinearChannel(ptr %31)
  %33 = load %Value, ptr %32, align 4
  %34 = call %Unit @free(ptr %32)
  store %Value %33, ptr %30, align 4
  br label %match-cont

tagBranch3:                                       ; preds = %loop
  %35 = load ptr, ptr %c, align 8
  %36 = call ptr @_ReadLinearChannel(ptr %35)
  %37 = load i32, ptr %36, align 4
  %38 = call %Unit @free(ptr %36)
  store i32 %37, ptr %k, align 4
  %39 = load ptr, ptr %c, align 8
  %40 = call %Unit @_WriteProjection(ptr %39, i32 1)
  %k2 = load i32, ptr %k, align 4
  %41 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %k2
  %42 = load ptr, ptr %c, align 8
  %43 = call ptr @_ReadLinearChannel(ptr %42)
  %44 = load %Value, ptr %43, align 4
  %45 = call %Unit @free(ptr %43)
  store %Value %44, ptr %41, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %tagBranch2, %accessAfter, %loop
  %46 = call i32 (ptr, ...) @printf(ptr @4)
  %data3 = load [10 x %Value], ptr %data, align 4
  %47 = call %Unit @"Database::PrintDatabase"([10 x %Value] %data3)
  %48 = load ptr, ptr %c, align 8
  %49 = call i1 @_ShouldLinearLoop(ptr %48)
  br i1 %49, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %a = alloca %"(Unit + Value)", align 8
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
  %4 = load ptr, ptr %rqs, align 8
  %5 = call i1 @_ShouldLinearLoop(ptr %4)
  br i1 %5, label %loop, label %rest6

loop:                                             ; preds = %match-cont5, %entry
  br label %aw-cond

aw-cond:                                          ; preds = %loop1, %loop
  %6 = load ptr, ptr %setRq, align 8
  %7 = call i1 @_OC_isPresent(ptr %6)
  br i1 %7, label %aw-then, label %rest

aw-then:                                          ; preds = %aw-cond
  %8 = load ptr, ptr %setRq, align 8
  %9 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %8)
  br i1 %9, label %loop1, label %rest

loop1:                                            ; preds = %aw-then
  %10 = load ptr, ptr %db, align 8
  %11 = call %Unit @_ContractChannel(ptr %10)
  %12 = load ptr, ptr %db, align 8
  %13 = call %Unit @_WriteProjection(ptr %12, i32 2)
  %14 = load ptr, ptr %setRq, align 8
  %15 = call ptr @_ReadLinearChannel(ptr %14)
  %16 = load i32, ptr %15, align 4
  %17 = call %Unit @free(ptr %15)
  %18 = call ptr @malloc(i32 4)
  store i32 %16, ptr %18, align 4
  %19 = load ptr, ptr %db, align 8
  %20 = call %Unit @_WriteChannel(ptr %19, ptr %18)
  %21 = load ptr, ptr %setRq, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load %Value, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  %25 = call ptr @malloc(i32 4)
  store %Value %23, ptr %25, align 4
  %26 = load ptr, ptr %db, align 8
  %27 = call %Unit @_WriteChannel(ptr %26, ptr %25)
  br label %aw-cond

rest:                                             ; preds = %aw-then, %aw-cond
  %28 = load ptr, ptr %db, align 8
  %29 = call %Unit @_ContractChannel(ptr %28)
  %30 = load ptr, ptr %rqs, align 8
  %31 = call i32 @_ReadLinearProjection(ptr %30)
  switch i32 %31, label %match-cont5 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %rest
  %32 = load ptr, ptr %db, align 8
  %33 = call %Unit @_WriteProjection(ptr %32, i32 1)
  %34 = load ptr, ptr %rqs, align 8
  %35 = call ptr @_ReadLinearChannel(ptr %34)
  %36 = load i32, ptr %35, align 4
  %37 = call %Unit @free(ptr %35)
  %38 = call ptr @malloc(i32 4)
  store i32 %36, ptr %38, align 4
  %39 = load ptr, ptr %db, align 8
  %40 = call %Unit @_WriteChannel(ptr %39, ptr %38)
  %41 = load ptr, ptr %db, align 8
  %42 = call ptr @_ReadLinearChannel(ptr %41)
  %43 = load %"(Unit + Value)", ptr %42, align 4
  %44 = call %Unit @free(ptr %42)
  store %"(Unit + Value)" %43, ptr %a, align 4
  %a2 = load %"(Unit + Value)", ptr %a, align 4
  %45 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %a2, ptr %45, align 4
  %46 = load ptr, ptr %rqs, align 8
  %47 = call %Unit @_WriteChannel(ptr %46, ptr %45)
  br label %match-cont5

tagBranch2:                                       ; preds = %rest
  %48 = load ptr, ptr %db, align 8
  %49 = call %Unit @_WriteProjection(ptr %48, i32 2)
  %50 = load ptr, ptr %rqs, align 8
  %51 = call ptr @_ReadLinearChannel(ptr %50)
  %52 = load i32, ptr %51, align 4
  %53 = call %Unit @free(ptr %51)
  %54 = call ptr @malloc(i32 4)
  store i32 %52, ptr %54, align 4
  %55 = load ptr, ptr %db, align 8
  %56 = call %Unit @_WriteChannel(ptr %55, ptr %54)
  %57 = load ptr, ptr %rqs, align 8
  %58 = call ptr @_ReadLinearChannel(ptr %57)
  %59 = load %Value, ptr %58, align 4
  %60 = call %Unit @free(ptr %58)
  %61 = call ptr @malloc(i32 4)
  store %Value %59, ptr %61, align 4
  %62 = load ptr, ptr %db, align 8
  %63 = call %Unit @_WriteChannel(ptr %62, ptr %61)
  br label %match-cont5

tagBranch3:                                       ; preds = %rest
  %64 = call i32 (ptr, ...) @printf(ptr @5)
  %65 = load ptr, ptr %db, align 8
  %66 = call %Unit @_WriteProjection(ptr %65, i32 3)
  %67 = load ptr, ptr %rqs, align 8
  %68 = call ptr @_ReadLinearChannel(ptr %67)
  %69 = load i32, ptr %68, align 4
  %70 = call %Unit @free(ptr %68)
  %71 = call ptr @malloc(i32 4)
  store i32 %69, ptr %71, align 4
  %72 = load ptr, ptr %db, align 8
  %73 = call %Unit @_WriteChannel(ptr %72, ptr %71)
  %74 = load ptr, ptr %db, align 8
  %75 = call i32 @_ReadLinearProjection(ptr %74)
  switch i32 %75, label %match-cont [
    i32 1, label %tagBranch13
    i32 2, label %tagBranch24
  ]

tagBranch13:                                      ; preds = %tagBranch3
  %76 = load ptr, ptr %rqs, align 8
  %77 = call %Unit @_WriteProjection(ptr %76, i32 1)
  %78 = load ptr, ptr %rqs, align 8
  %79 = call ptr @_ReadLinearChannel(ptr %78)
  %80 = load %Value, ptr %79, align 4
  %81 = call %Unit @free(ptr %79)
  %82 = call ptr @malloc(i32 4)
  store %Value %80, ptr %82, align 4
  %83 = load ptr, ptr %db, align 8
  %84 = call %Unit @_WriteChannel(ptr %83, ptr %82)
  br label %match-cont

tagBranch24:                                      ; preds = %tagBranch3
  %85 = load ptr, ptr %rqs, align 8
  %86 = call %Unit @_WriteProjection(ptr %85, i32 2)
  %87 = load ptr, ptr %db, align 8
  %88 = call ptr @_ReadLinearChannel(ptr %87)
  %89 = load %Value, ptr %88, align 4
  %90 = call %Unit @free(ptr %88)
  %91 = call ptr @malloc(i32 4)
  store %Value %89, ptr %91, align 4
  %92 = load ptr, ptr %rqs, align 8
  %93 = call %Unit @_WriteChannel(ptr %92, ptr %91)
  %94 = load ptr, ptr %rqs, align 8
  %95 = call ptr @_ReadLinearChannel(ptr %94)
  %96 = load %Value, ptr %95, align 4
  %97 = call %Unit @free(ptr %95)
  %98 = call ptr @malloc(i32 4)
  store %Value %96, ptr %98, align 4
  %99 = load ptr, ptr %db, align 8
  %100 = call %Unit @_WriteChannel(ptr %99, ptr %98)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch24, %tagBranch13, %tagBranch3
  br label %match-cont5

match-cont5:                                      ; preds = %match-cont, %tagBranch2, %tagBranch1, %rest
  %101 = load ptr, ptr %rqs, align 8
  %102 = call i1 @_ShouldLinearLoop(ptr %101)
  br i1 %102, label %loop, label %rest6

rest6:                                            ; preds = %match-cont5, %entry
  %103 = load ptr, ptr %setRq, align 8
  %104 = call i1 @_ShouldLinearLoop(ptr %103)
  br i1 %104, label %loop7, label %rest8

loop7:                                            ; preds = %loop7, %rest6
  %105 = load ptr, ptr %db, align 8
  %106 = call %Unit @_ContractChannel(ptr %105)
  %107 = load ptr, ptr %db, align 8
  %108 = call %Unit @_WriteProjection(ptr %107, i32 2)
  %109 = load ptr, ptr %setRq, align 8
  %110 = call ptr @_ReadLinearChannel(ptr %109)
  %111 = load i32, ptr %110, align 4
  %112 = call %Unit @free(ptr %110)
  %113 = call ptr @malloc(i32 4)
  store i32 %111, ptr %113, align 4
  %114 = load ptr, ptr %db, align 8
  %115 = call %Unit @_WriteChannel(ptr %114, ptr %113)
  %116 = load ptr, ptr %setRq, align 8
  %117 = call ptr @_ReadLinearChannel(ptr %116)
  %118 = load %Value, ptr %117, align 4
  %119 = call %Unit @free(ptr %117)
  %120 = call ptr @malloc(i32 4)
  store %Value %118, ptr %120, align 4
  %121 = load ptr, ptr %db, align 8
  %122 = call %Unit @_WriteChannel(ptr %121, ptr %120)
  %123 = load ptr, ptr %setRq, align 8
  %124 = call i1 @_ShouldLinearLoop(ptr %123)
  br i1 %124, label %loop7, label %rest8

rest8:                                            ; preds = %loop7, %rest6
  %125 = load ptr, ptr %db, align 8
  %126 = call %Unit @_WeakenChannel(ptr %125)
  %127 = call ptr @malloc(i32 4)
  store i32 0, ptr %127, align 4
  %128 = load ptr, ptr %c, align 8
  %129 = call %Unit @_WriteChannel(ptr %128, ptr %127)
  ret %Unit zeroinitializer
}

define %Unit @requests(ptr %0) {
entry:
  %v = alloca %Value, align 8
  %e.0 = alloca %Unit, align 8
  %1 = alloca %"(Unit + Value)", align 8
  %v.0 = alloca %Value, align 8
  %e = alloca %Unit, align 8
  %2 = alloca %"(Unit + Value)", align 8
  %opt = alloca %"(Unit + Value)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_ContractChannel(ptr %3)
  %5 = load ptr, ptr %c, align 8
  %6 = call %Unit @_WriteProjection(ptr %5, i32 1)
  %7 = call ptr @malloc(i32 4)
  store i32 4, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = load ptr, ptr %c, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load %"(Unit + Value)", ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  store %"(Unit + Value)" %12, ptr %opt, align 4
  %14 = call i32 (ptr, ...) @printf(ptr @6)
  %opt1 = load %"(Unit + Value)", ptr %opt, align 4
  store %"(Unit + Value)" %opt1, ptr %2, align 4
  %15 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  switch i32 %16, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %17 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  %18 = load %Unit, ptr %17, align 1
  store %Unit %18, ptr %e, align 1
  %19 = call i32 (ptr, ...) @printf(ptr @7)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %20 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  %21 = load %Value, ptr %20, align 4
  store %Value %21, ptr %v.0, align 4
  %22 = getelementptr %Value, ptr %v.0, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  %24 = call i32 (ptr, ...) @printf(ptr @8, i32 %23)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %25 = load ptr, ptr %c, align 8
  %26 = call %Unit @_ContractChannel(ptr %25)
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteProjection(ptr %27, i32 1)
  %29 = call ptr @malloc(i32 4)
  store i32 20, ptr %29, align 4
  %30 = load ptr, ptr %c, align 8
  %31 = call %Unit @_WriteChannel(ptr %30, ptr %29)
  %32 = load ptr, ptr %c, align 8
  %33 = call ptr @_ReadLinearChannel(ptr %32)
  %34 = load %"(Unit + Value)", ptr %33, align 4
  %35 = call %Unit @free(ptr %33)
  store %"(Unit + Value)" %34, ptr %opt, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @9)
  %opt2 = load %"(Unit + Value)", ptr %opt, align 4
  store %"(Unit + Value)" %opt2, ptr %1, align 4
  %37 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 0
  %38 = load i32, ptr %37, align 4
  switch i32 %38, label %match-cont5 [
    i32 1, label %tagBranch13
    i32 2, label %tagBranch24
  ]

tagBranch13:                                      ; preds = %match-cont
  %39 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %40 = load %Unit, ptr %39, align 1
  store %Unit %40, ptr %e.0, align 1
  %41 = call i32 (ptr, ...) @printf(ptr @10)
  br label %match-cont5

tagBranch24:                                      ; preds = %match-cont
  %42 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %43 = load %Value, ptr %42, align 4
  store %Value %43, ptr %v, align 4
  %44 = getelementptr %Value, ptr %v, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  %46 = call i32 (ptr, ...) @printf(ptr @11, i32 %45)
  br label %match-cont5

match-cont5:                                      ; preds = %tagBranch24, %tagBranch13, %match-cont
  %47 = load ptr, ptr %c, align 8
  %48 = call %Unit @_WeakenChannel(ptr %47)
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

define private %Unit @"Database::PrintDatabase"([10 x %Value] %0) {
entry:
  %u = alloca %Unit, align 8
  %v = alloca %Value, align 8
  %1 = alloca %"(Unit + Value)", align 8
  %2 = alloca %"(Unit + Value)", align 8
  %3 = alloca %"(Unit + Value)", align 8
  %i = alloca i32, align 4
  %data = alloca [10 x %Value], align 8
  store [10 x %Value] %0, ptr %data, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %4 = icmp slt i32 %i1, 10
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, ptr %i, align 4
  %5 = icmp slt i32 %i2, 10
  br i1 %5, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %6 = icmp sge i32 %i2, 0
  br i1 %6, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %7 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %i2
  %8 = load %Value, ptr %7, align 4
  %9 = getelementptr %"(Unit + Value)", ptr %3, i32 0, i32 0
  store i32 2, ptr %9, align 4
  %10 = getelementptr %"(Unit + Value)", ptr %3, i32 0, i32 1
  store %Value %8, ptr %10, align 4
  %11 = load %"(Unit + Value)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %12 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 0
  store i32 1, ptr %12, align 4
  %13 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %13, align 1
  %14 = load %"(Unit + Value)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + Value)" [ %11, %accessGTZ ], [ %14, %accessBad ]
  store %"(Unit + Value)" %arrayAccess, ptr %1, align 4
  %15 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  switch i32 %16, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %17 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %18 = load %Value, ptr %17, align 4
  store %Value %18, ptr %v, align 4
  %19 = getelementptr %Value, ptr %v, i32 0, i32 0
  %20 = load i32, ptr %19, align 4
  %21 = call i32 (ptr, ...) @printf(ptr @0, i32 %20)
  br label %match-cont

tagBranch1:                                       ; preds = %accessAfter
  %22 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %23 = load %Unit, ptr %22, align 1
  store %Unit %23, ptr %u, align 1
  %24 = call i32 (ptr, ...) @printf(ptr @1)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %accessAfter
  %i3 = load i32, ptr %i, align 4
  %25 = add nsw i32 %i3, 1
  store i32 %25, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %26 = icmp slt i32 %i4, 10
  br i1 %26, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  %27 = call i32 (ptr, ...) @printf(ptr @2)
  ret %Unit zeroinitializer
}

declare i1 @_ShouldLinearLoop(ptr)

declare i32 @_ReadLinearProjection(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare %Unit @_WriteProjection(ptr, i32)

declare ptr @_Execute(ptr)

declare i1 @_OC_isPresent(ptr)

declare i1 @_ShouldLinearAcceptWhileLoop(ptr)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WeakenChannel(ptr)
