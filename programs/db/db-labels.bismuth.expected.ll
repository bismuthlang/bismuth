; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%Value = type { i32 }
%"(Unit + Value)" = type { i32, [4 x i8] }
%OptVal = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [25 x i8] c"Initial Database State:\0A\00", align 1
@3 = private unnamed_addr constant [20 x i8] c"Database Updated: \0A\00", align 1
@4 = private unnamed_addr constant [25 x i8] c"Read Request for 4 got: \00", align 1
@5 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@6 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@7 = private unnamed_addr constant [26 x i8] c"Read Request for 20 got: \00", align 1
@8 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define %Unit @Database(ptr %0) {
entry:
  %key = alloca i32, align 4
  %v = alloca %Value, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + Value)", align 8
  %2 = alloca %"(Unit + Value)", align 8
  %3 = alloca %"(Unit + Value)", align 8
  %k = alloca i32, align 4
  %4 = alloca %"(Unit + Value)", align 8
  %5 = alloca %"(Unit + Value)", align 8
  %data = alloca [10 x %Value], align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %6 = call i32 (ptr, ...) @printf(ptr @2)
  %data1 = load [10 x %Value], ptr %data, align 4
  %7 = call %Unit @"Database::PrintDatabase"([10 x %Value] %data1)
  %8 = load ptr, ptr %c, align 8
  %9 = call i1 @_ShouldLinearLoop(ptr %8)
  br i1 %9, label %loop, label %rest

loop:                                             ; preds = %match-cont13, %entry
  %10 = load ptr, ptr %c, align 8
  %11 = call i32 @_ReadLinearProjection(ptr %10)
  switch i32 %11, label %match-cont13 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop
  %12 = load ptr, ptr %c, align 8
  %13 = call ptr @_ReadLinearChannel(ptr %12)
  %14 = load i32, ptr %13, align 4
  %15 = call %Unit @free(ptr %13)
  %16 = icmp slt i32 %14, 10
  br i1 %16, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %tagBranch1
  %17 = icmp sge i32 %14, 0
  br i1 %17, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %18 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %14
  %19 = load %Value, ptr %18, align 4
  %20 = getelementptr %"(Unit + Value)", ptr %5, i32 0, i32 0
  store i32 2, ptr %20, align 4
  %21 = getelementptr %"(Unit + Value)", ptr %5, i32 0, i32 1
  store %Value %19, ptr %21, align 4
  %22 = load %"(Unit + Value)", ptr %5, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %tagBranch1
  %23 = getelementptr %"(Unit + Value)", ptr %4, i32 0, i32 0
  store i32 1, ptr %23, align 4
  %24 = getelementptr %"(Unit + Value)", ptr %4, i32 0, i32 1
  store %Unit zeroinitializer, ptr %24, align 1
  %25 = load %"(Unit + Value)", ptr %4, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + Value)" [ %22, %accessGTZ ], [ %25, %accessBad ]
  %26 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %arrayAccess, ptr %26, align 4
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  br label %match-cont13

tagBranch2:                                       ; preds = %loop
  %29 = load ptr, ptr %c, align 8
  %30 = call ptr @_ReadLinearChannel(ptr %29)
  %31 = load i32, ptr %30, align 4
  %32 = call %Unit @free(ptr %30)
  store i32 %31, ptr %k, align 4
  %k2 = load i32, ptr %k, align 4
  %33 = icmp slt i32 %k2, 10
  br i1 %33, label %accessLTL3, label %accessBad5

accessLTL3:                                       ; preds = %tagBranch2
  %34 = icmp sge i32 %k2, 0
  br i1 %34, label %accessGTZ4, label %accessBad5

accessGTZ4:                                       ; preds = %accessLTL3
  %35 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %k2
  %36 = load %Value, ptr %35, align 4
  %37 = getelementptr %"(Unit + Value)", ptr %3, i32 0, i32 0
  store i32 2, ptr %37, align 4
  %38 = getelementptr %"(Unit + Value)", ptr %3, i32 0, i32 1
  store %Value %36, ptr %38, align 4
  %39 = load %"(Unit + Value)", ptr %3, align 4
  br label %accessAfter6

accessBad5:                                       ; preds = %accessLTL3, %tagBranch2
  %40 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 0
  store i32 1, ptr %40, align 4
  %41 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %41, align 1
  %42 = load %"(Unit + Value)", ptr %2, align 4
  br label %accessAfter6

accessAfter6:                                     ; preds = %accessBad5, %accessGTZ4
  %arrayAccess7 = phi %"(Unit + Value)" [ %39, %accessGTZ4 ], [ %42, %accessBad5 ]
  store %"(Unit + Value)" %arrayAccess7, ptr %1, align 4
  %43 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 0
  %44 = load i32, ptr %43, align 4
  switch i32 %44, label %match-cont [
    i32 1, label %tagBranch18
    i32 2, label %tagBranch29
  ]

tagBranch18:                                      ; preds = %accessAfter6
  %45 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %46 = load %Unit, ptr %45, align 1
  store %Unit %46, ptr %u, align 1
  %47 = load ptr, ptr %c, align 8
  %48 = call %Unit @_WriteProjection(ptr %47, i32 1)
  br label %match-cont

tagBranch29:                                      ; preds = %accessAfter6
  %49 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %50 = load %Value, ptr %49, align 4
  store %Value %50, ptr %v, align 4
  %51 = load ptr, ptr %c, align 8
  %52 = call %Unit @_WriteProjection(ptr %51, i32 2)
  %v10 = load %Value, ptr %v, align 4
  %53 = call ptr @malloc(i32 4)
  store %Value %v10, ptr %53, align 4
  %54 = load ptr, ptr %c, align 8
  %55 = call %Unit @_WriteChannel(ptr %54, ptr %53)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch29, %tagBranch18, %accessAfter6
  %k11 = load i32, ptr %k, align 4
  %56 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %k11
  %57 = load ptr, ptr %c, align 8
  %58 = call ptr @_ReadLinearChannel(ptr %57)
  %59 = load %Value, ptr %58, align 4
  %60 = call %Unit @free(ptr %58)
  store %Value %59, ptr %56, align 4
  br label %match-cont13

tagBranch3:                                       ; preds = %loop
  %61 = load ptr, ptr %c, align 8
  %62 = call ptr @_ReadLinearChannel(ptr %61)
  %63 = load i32, ptr %62, align 4
  %64 = call %Unit @free(ptr %62)
  store i32 %63, ptr %key, align 4
  %key12 = load i32, ptr %key, align 4
  %65 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %key12
  %66 = load ptr, ptr %c, align 8
  %67 = call ptr @_ReadLinearChannel(ptr %66)
  %68 = load %Value, ptr %67, align 4
  %69 = call %Unit @free(ptr %67)
  store %Value %68, ptr %65, align 4
  br label %match-cont13

match-cont13:                                     ; preds = %tagBranch3, %match-cont, %accessAfter, %loop
  %70 = call i32 (ptr, ...) @printf(ptr @3)
  %data14 = load [10 x %Value], ptr %data, align 4
  %71 = call %Unit @"Database::PrintDatabase"([10 x %Value] %data14)
  %72 = load ptr, ptr %c, align 8
  %73 = call i1 @_ShouldLinearLoop(ptr %72)
  br i1 %73, label %loop, label %rest

rest:                                             ; preds = %match-cont13, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %a = alloca %OptVal, align 8
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
  %13 = call %Unit @_WriteProjection(ptr %12, i32 3)
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
  %43 = load %OptVal, ptr %42, align 4
  %44 = call %Unit @free(ptr %42)
  store %OptVal %43, ptr %a, align 4
  %a2 = load %OptVal, ptr %a, align 4
  %45 = call ptr @malloc(i32 8)
  store %OptVal %a2, ptr %45, align 4
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
  %57 = load ptr, ptr %db, align 8
  %58 = call i32 @_ReadLinearProjection(ptr %57)
  switch i32 %58, label %match-cont [
    i32 1, label %tagBranch13
    i32 2, label %tagBranch24
  ]

tagBranch13:                                      ; preds = %tagBranch2
  %59 = load ptr, ptr %rqs, align 8
  %60 = call %Unit @_WriteProjection(ptr %59, i32 1)
  %61 = load ptr, ptr %rqs, align 8
  %62 = call ptr @_ReadLinearChannel(ptr %61)
  %63 = load %Value, ptr %62, align 4
  %64 = call %Unit @free(ptr %62)
  %65 = call ptr @malloc(i32 4)
  store %Value %63, ptr %65, align 4
  %66 = load ptr, ptr %db, align 8
  %67 = call %Unit @_WriteChannel(ptr %66, ptr %65)
  br label %match-cont

tagBranch24:                                      ; preds = %tagBranch2
  %68 = load ptr, ptr %rqs, align 8
  %69 = call %Unit @_WriteProjection(ptr %68, i32 2)
  %70 = load ptr, ptr %db, align 8
  %71 = call ptr @_ReadLinearChannel(ptr %70)
  %72 = load %Value, ptr %71, align 4
  %73 = call %Unit @free(ptr %71)
  %74 = call ptr @malloc(i32 4)
  store %Value %72, ptr %74, align 4
  %75 = load ptr, ptr %rqs, align 8
  %76 = call %Unit @_WriteChannel(ptr %75, ptr %74)
  %77 = load ptr, ptr %rqs, align 8
  %78 = call ptr @_ReadLinearChannel(ptr %77)
  %79 = load %Value, ptr %78, align 4
  %80 = call %Unit @free(ptr %78)
  %81 = call ptr @malloc(i32 4)
  store %Value %79, ptr %81, align 4
  %82 = load ptr, ptr %db, align 8
  %83 = call %Unit @_WriteChannel(ptr %82, ptr %81)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch24, %tagBranch13, %tagBranch2
  br label %match-cont5

tagBranch3:                                       ; preds = %rest
  %84 = load ptr, ptr %db, align 8
  %85 = call %Unit @_WriteProjection(ptr %84, i32 3)
  %86 = load ptr, ptr %rqs, align 8
  %87 = call ptr @_ReadLinearChannel(ptr %86)
  %88 = load i32, ptr %87, align 4
  %89 = call %Unit @free(ptr %87)
  %90 = call ptr @malloc(i32 4)
  store i32 %88, ptr %90, align 4
  %91 = load ptr, ptr %db, align 8
  %92 = call %Unit @_WriteChannel(ptr %91, ptr %90)
  %93 = load ptr, ptr %rqs, align 8
  %94 = call ptr @_ReadLinearChannel(ptr %93)
  %95 = load %Value, ptr %94, align 4
  %96 = call %Unit @free(ptr %94)
  %97 = call ptr @malloc(i32 4)
  store %Value %95, ptr %97, align 4
  %98 = load ptr, ptr %db, align 8
  %99 = call %Unit @_WriteChannel(ptr %98, ptr %97)
  br label %match-cont5

match-cont5:                                      ; preds = %tagBranch3, %match-cont, %tagBranch1, %rest
  %100 = load ptr, ptr %rqs, align 8
  %101 = call i1 @_ShouldLinearLoop(ptr %100)
  br i1 %101, label %loop, label %rest6

rest6:                                            ; preds = %match-cont5, %entry
  %102 = load ptr, ptr %setRq, align 8
  %103 = call i1 @_ShouldLinearLoop(ptr %102)
  br i1 %103, label %loop7, label %rest8

loop7:                                            ; preds = %loop7, %rest6
  %104 = load ptr, ptr %db, align 8
  %105 = call %Unit @_ContractChannel(ptr %104)
  %106 = load ptr, ptr %db, align 8
  %107 = call %Unit @_WriteProjection(ptr %106, i32 3)
  %108 = load ptr, ptr %setRq, align 8
  %109 = call ptr @_ReadLinearChannel(ptr %108)
  %110 = load i32, ptr %109, align 4
  %111 = call %Unit @free(ptr %109)
  %112 = call ptr @malloc(i32 4)
  store i32 %110, ptr %112, align 4
  %113 = load ptr, ptr %db, align 8
  %114 = call %Unit @_WriteChannel(ptr %113, ptr %112)
  %115 = load ptr, ptr %setRq, align 8
  %116 = call ptr @_ReadLinearChannel(ptr %115)
  %117 = load %Value, ptr %116, align 4
  %118 = call %Unit @free(ptr %116)
  %119 = call ptr @malloc(i32 4)
  store %Value %117, ptr %119, align 4
  %120 = load ptr, ptr %db, align 8
  %121 = call %Unit @_WriteChannel(ptr %120, ptr %119)
  %122 = load ptr, ptr %setRq, align 8
  %123 = call i1 @_ShouldLinearLoop(ptr %122)
  br i1 %123, label %loop7, label %rest8

rest8:                                            ; preds = %loop7, %rest6
  %124 = load ptr, ptr %db, align 8
  %125 = call %Unit @_WeakenChannel(ptr %124)
  %126 = call ptr @malloc(i32 4)
  store i32 0, ptr %126, align 4
  %127 = load ptr, ptr %c, align 8
  %128 = call %Unit @_WriteChannel(ptr %127, ptr %126)
  ret %Unit zeroinitializer
}

define %Unit @requests(ptr %0) {
entry:
  %v = alloca %Value, align 8
  %u.0 = alloca %Unit, align 8
  %1 = alloca %OptVal, align 8
  %v.0 = alloca %Value, align 8
  %u = alloca %Unit, align 8
  %2 = alloca %OptVal, align 8
  %opt = alloca %OptVal, align 8
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
  %12 = load %OptVal, ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  store %OptVal %12, ptr %opt, align 4
  %14 = call i32 (ptr, ...) @printf(ptr @4)
  %opt1 = load %OptVal, ptr %opt, align 4
  store %OptVal %opt1, ptr %2, align 4
  %15 = getelementptr %OptVal, ptr %2, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  switch i32 %16, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %17 = getelementptr %OptVal, ptr %2, i32 0, i32 1
  %18 = load %Unit, ptr %17, align 1
  store %Unit %18, ptr %u, align 1
  %19 = call i32 (ptr, ...) @printf(ptr @5)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %20 = getelementptr %OptVal, ptr %2, i32 0, i32 1
  %21 = load %Value, ptr %20, align 4
  store %Value %21, ptr %v.0, align 4
  %22 = getelementptr %Value, ptr %v.0, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  %24 = call i32 (ptr, ...) @printf(ptr @6, i32 %23)
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
  %34 = load %OptVal, ptr %33, align 4
  %35 = call %Unit @free(ptr %33)
  store %OptVal %34, ptr %opt, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @7)
  %opt2 = load %OptVal, ptr %opt, align 4
  store %OptVal %opt2, ptr %1, align 4
  %37 = getelementptr %OptVal, ptr %1, i32 0, i32 0
  %38 = load i32, ptr %37, align 4
  switch i32 %38, label %match-cont5 [
    i32 1, label %tagBranch13
    i32 2, label %tagBranch24
  ]

tagBranch13:                                      ; preds = %match-cont
  %39 = getelementptr %OptVal, ptr %1, i32 0, i32 1
  %40 = load %Unit, ptr %39, align 1
  store %Unit %40, ptr %u.0, align 1
  %41 = call i32 (ptr, ...) @printf(ptr @8)
  br label %match-cont5

tagBranch24:                                      ; preds = %match-cont
  %42 = getelementptr %OptVal, ptr %1, i32 0, i32 1
  %43 = load %Value, ptr %42, align 4
  store %Value %43, ptr %v, align 4
  %44 = getelementptr %Value, ptr %v, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  %46 = call i32 (ptr, ...) @printf(ptr @9, i32 %45)
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
  %v = alloca %Value, align 8
  %u = alloca %Unit, align 8
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
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %17 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %18 = load %Unit, ptr %17, align 1
  store %Unit %18, ptr %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %19 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  %20 = load %Value, ptr %19, align 4
  store %Value %20, ptr %v, align 4
  %21 = getelementptr %Value, ptr %v, i32 0, i32 0
  %22 = load i32, ptr %21, align 4
  %23 = call i32 (ptr, ...) @printf(ptr @0, i32 %22)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i3 = load i32, ptr %i, align 4
  %24 = add nsw i32 %i3, 1
  store i32 %24, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %25 = icmp slt i32 %i4, 10
  br i1 %25, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  %26 = call i32 (ptr, ...) @printf(ptr @1)
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
