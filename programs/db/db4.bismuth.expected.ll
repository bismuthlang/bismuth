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
  br label %aw-cond

aw-cond:                                          ; preds = %loop, %entry
  br i1 true, label %aw-then, label %rest

aw-then:                                          ; preds = %aw-cond
  %4 = load ptr, ptr %setRq, align 8
  %5 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %4)
  br i1 %5, label %loop, label %rest

loop:                                             ; preds = %aw-then
  %6 = load ptr, ptr %db, align 8
  %7 = call %Unit @_ContractChannel(ptr %6)
  %8 = load ptr, ptr %db, align 8
  %9 = call %Unit @_WriteProjection(ptr %8, i32 2)
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
  br label %aw-cond

rest:                                             ; preds = %aw-then, %aw-cond
  %24 = load ptr, ptr %rqs, align 8
  %25 = call i1 @_ShouldLinearLoop(ptr %24)
  br i1 %25, label %loop1, label %rest6

loop1:                                            ; preds = %match-cont5, %rest
  %26 = load ptr, ptr %db, align 8
  %27 = call %Unit @_ContractChannel(ptr %26)
  %28 = load ptr, ptr %rqs, align 8
  %29 = call i32 @_ReadLinearProjection(ptr %28)
  switch i32 %29, label %match-cont5 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop1
  %30 = load ptr, ptr %db, align 8
  %31 = call %Unit @_WriteProjection(ptr %30, i32 1)
  %32 = load ptr, ptr %rqs, align 8
  %33 = call ptr @_ReadLinearChannel(ptr %32)
  %34 = load i32, ptr %33, align 4
  %35 = call %Unit @free(ptr %33)
  %36 = call ptr @malloc(i32 4)
  store i32 %34, ptr %36, align 4
  %37 = load ptr, ptr %db, align 8
  %38 = call %Unit @_WriteChannel(ptr %37, ptr %36)
  %39 = load ptr, ptr %db, align 8
  %40 = call ptr @_ReadLinearChannel(ptr %39)
  %41 = load %"(Unit + Value)", ptr %40, align 4
  %42 = call %Unit @free(ptr %40)
  store %"(Unit + Value)" %41, ptr %a, align 4
  %a2 = load %"(Unit + Value)", ptr %a, align 4
  %43 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %a2, ptr %43, align 4
  %44 = load ptr, ptr %rqs, align 8
  %45 = call %Unit @_WriteChannel(ptr %44, ptr %43)
  br label %match-cont5

tagBranch2:                                       ; preds = %loop1
  %46 = load ptr, ptr %db, align 8
  %47 = call %Unit @_WriteProjection(ptr %46, i32 2)
  %48 = load ptr, ptr %rqs, align 8
  %49 = call ptr @_ReadLinearChannel(ptr %48)
  %50 = load i32, ptr %49, align 4
  %51 = call %Unit @free(ptr %49)
  %52 = call ptr @malloc(i32 4)
  store i32 %50, ptr %52, align 4
  %53 = load ptr, ptr %db, align 8
  %54 = call %Unit @_WriteChannel(ptr %53, ptr %52)
  %55 = load ptr, ptr %rqs, align 8
  %56 = call ptr @_ReadLinearChannel(ptr %55)
  %57 = load %Value, ptr %56, align 4
  %58 = call %Unit @free(ptr %56)
  %59 = call ptr @malloc(i32 4)
  store %Value %57, ptr %59, align 4
  %60 = load ptr, ptr %db, align 8
  %61 = call %Unit @_WriteChannel(ptr %60, ptr %59)
  br label %match-cont5

tagBranch3:                                       ; preds = %loop1
  %62 = call i32 (ptr, ...) @printf(ptr @5)
  %63 = load ptr, ptr %db, align 8
  %64 = call %Unit @_WriteProjection(ptr %63, i32 3)
  %65 = load ptr, ptr %rqs, align 8
  %66 = call ptr @_ReadLinearChannel(ptr %65)
  %67 = load i32, ptr %66, align 4
  %68 = call %Unit @free(ptr %66)
  %69 = call ptr @malloc(i32 4)
  store i32 %67, ptr %69, align 4
  %70 = load ptr, ptr %db, align 8
  %71 = call %Unit @_WriteChannel(ptr %70, ptr %69)
  %72 = load ptr, ptr %db, align 8
  %73 = call i32 @_ReadLinearProjection(ptr %72)
  switch i32 %73, label %match-cont [
    i32 1, label %tagBranch13
    i32 2, label %tagBranch24
  ]

tagBranch13:                                      ; preds = %tagBranch3
  %74 = load ptr, ptr %rqs, align 8
  %75 = call %Unit @_WriteProjection(ptr %74, i32 1)
  %76 = load ptr, ptr %rqs, align 8
  %77 = call ptr @_ReadLinearChannel(ptr %76)
  %78 = load %Value, ptr %77, align 4
  %79 = call %Unit @free(ptr %77)
  %80 = call ptr @malloc(i32 4)
  store %Value %78, ptr %80, align 4
  %81 = load ptr, ptr %db, align 8
  %82 = call %Unit @_WriteChannel(ptr %81, ptr %80)
  br label %match-cont

tagBranch24:                                      ; preds = %tagBranch3
  %83 = load ptr, ptr %rqs, align 8
  %84 = call %Unit @_WriteProjection(ptr %83, i32 2)
  %85 = load ptr, ptr %db, align 8
  %86 = call ptr @_ReadLinearChannel(ptr %85)
  %87 = load %Value, ptr %86, align 4
  %88 = call %Unit @free(ptr %86)
  %89 = call ptr @malloc(i32 4)
  store %Value %87, ptr %89, align 4
  %90 = load ptr, ptr %rqs, align 8
  %91 = call %Unit @_WriteChannel(ptr %90, ptr %89)
  %92 = load ptr, ptr %rqs, align 8
  %93 = call ptr @_ReadLinearChannel(ptr %92)
  %94 = load %Value, ptr %93, align 4
  %95 = call %Unit @free(ptr %93)
  %96 = call ptr @malloc(i32 4)
  store %Value %94, ptr %96, align 4
  %97 = load ptr, ptr %db, align 8
  %98 = call %Unit @_WriteChannel(ptr %97, ptr %96)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch24, %tagBranch13, %tagBranch3
  br label %match-cont5

match-cont5:                                      ; preds = %match-cont, %tagBranch2, %tagBranch1, %loop1
  %99 = load ptr, ptr %rqs, align 8
  %100 = call i1 @_ShouldLinearLoop(ptr %99)
  br i1 %100, label %loop1, label %rest6

rest6:                                            ; preds = %match-cont5, %rest
  %101 = load ptr, ptr %setRq, align 8
  %102 = call i1 @_ShouldLinearLoop(ptr %101)
  br i1 %102, label %loop7, label %rest8

loop7:                                            ; preds = %loop7, %rest6
  %103 = load ptr, ptr %db, align 8
  %104 = call %Unit @_ContractChannel(ptr %103)
  %105 = load ptr, ptr %db, align 8
  %106 = call %Unit @_WriteProjection(ptr %105, i32 2)
  %107 = load ptr, ptr %setRq, align 8
  %108 = call ptr @_ReadLinearChannel(ptr %107)
  %109 = load i32, ptr %108, align 4
  %110 = call %Unit @free(ptr %108)
  %111 = call ptr @malloc(i32 4)
  store i32 %109, ptr %111, align 4
  %112 = load ptr, ptr %db, align 8
  %113 = call %Unit @_WriteChannel(ptr %112, ptr %111)
  %114 = load ptr, ptr %setRq, align 8
  %115 = call ptr @_ReadLinearChannel(ptr %114)
  %116 = load %Value, ptr %115, align 4
  %117 = call %Unit @free(ptr %115)
  %118 = call ptr @malloc(i32 4)
  store %Value %116, ptr %118, align 4
  %119 = load ptr, ptr %db, align 8
  %120 = call %Unit @_WriteChannel(ptr %119, ptr %118)
  %121 = load ptr, ptr %setRq, align 8
  %122 = call i1 @_ShouldLinearLoop(ptr %121)
  br i1 %122, label %loop7, label %rest8

rest8:                                            ; preds = %loop7, %rest6
  %123 = load ptr, ptr %db, align 8
  %124 = call %Unit @_WeakenChannel(ptr %123)
  %125 = call ptr @malloc(i32 4)
  store i32 0, ptr %125, align 4
  %126 = load ptr, ptr %c, align 8
  %127 = call %Unit @_WriteChannel(ptr %126, ptr %125)
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

declare i1 @_ShouldLinearAcceptWhileLoop(ptr)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WeakenChannel(ptr)
