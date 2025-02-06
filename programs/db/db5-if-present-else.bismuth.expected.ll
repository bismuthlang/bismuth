; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + Value)" = type { i32, [4 x i8] }
%Value = type { i32 }
%OptVal = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [4 x i8] c"*, \00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@3 = private unnamed_addr constant [25 x i8] c"Initial Database State:\0A\00", align 1
@4 = private unnamed_addr constant [20 x i8] c"Database Updated: \0A\00", align 1
@5 = private unnamed_addr constant [19 x i8] c"Acceptif Present!\0A\00", align 1
@6 = private unnamed_addr constant [23 x i8] c"AcceptIf Not Present!\0A\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"72\0A\00", align 1
@8 = private unnamed_addr constant [25 x i8] c"Read Request for 4 got: \00", align 1
@9 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@10 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@11 = private unnamed_addr constant [26 x i8] c"Read Request for 20 got: \00", align 1
@12 = private unnamed_addr constant [7 x i8] c"empty\0A\00", align 1
@13 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

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
  br i1 %5, label %loop, label %rest5

loop:                                             ; preds = %match-cont4, %entry
  %6 = load ptr, ptr %setRq, align 8
  %7 = call i1 @_OC_isPresent(ptr %6)
  br i1 %7, label %ai-cond, label %ai-else

ai-cond:                                          ; preds = %loop
  %8 = load ptr, ptr %setRq, align 8
  %9 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %8)
  br i1 %9, label %ai-then, label %ai-else

ai-then:                                          ; preds = %ai-cond
  %10 = call i32 (ptr, ...) @printf(ptr @5)
  %11 = load ptr, ptr %db, align 8
  %12 = call %Unit @_ContractChannel(ptr %11)
  %13 = load ptr, ptr %db, align 8
  %14 = call %Unit @_WriteProjection(ptr %13, i32 2)
  %15 = load ptr, ptr %setRq, align 8
  %16 = call ptr @_ReadLinearChannel(ptr %15)
  %17 = load i32, ptr %16, align 4
  %18 = call %Unit @free(ptr %16)
  %19 = call ptr @malloc(i32 4)
  store i32 %17, ptr %19, align 4
  %20 = load ptr, ptr %db, align 8
  %21 = call %Unit @_WriteChannel(ptr %20, ptr %19)
  %22 = load ptr, ptr %setRq, align 8
  %23 = call ptr @_ReadLinearChannel(ptr %22)
  %24 = load %Value, ptr %23, align 4
  %25 = call %Unit @free(ptr %23)
  %26 = call ptr @malloc(i32 4)
  store %Value %24, ptr %26, align 4
  %27 = load ptr, ptr %db, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  br label %rest

ai-else:                                          ; preds = %ai-cond, %loop
  %29 = call i32 (ptr, ...) @printf(ptr @6)
  br label %rest

rest:                                             ; preds = %ai-else, %ai-then
  %30 = load ptr, ptr %db, align 8
  %31 = call %Unit @_ContractChannel(ptr %30)
  %32 = load ptr, ptr %rqs, align 8
  %33 = call i32 @_ReadLinearProjection(ptr %32)
  switch i32 %33, label %match-cont4 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %rest
  %34 = load ptr, ptr %db, align 8
  %35 = call %Unit @_WriteProjection(ptr %34, i32 1)
  %36 = load ptr, ptr %rqs, align 8
  %37 = call ptr @_ReadLinearChannel(ptr %36)
  %38 = load i32, ptr %37, align 4
  %39 = call %Unit @free(ptr %37)
  %40 = call ptr @malloc(i32 4)
  store i32 %38, ptr %40, align 4
  %41 = load ptr, ptr %db, align 8
  %42 = call %Unit @_WriteChannel(ptr %41, ptr %40)
  %43 = load ptr, ptr %db, align 8
  %44 = call ptr @_ReadLinearChannel(ptr %43)
  %45 = load %OptVal, ptr %44, align 4
  %46 = call %Unit @free(ptr %44)
  store %OptVal %45, ptr %a, align 4
  %a1 = load %OptVal, ptr %a, align 4
  %47 = call ptr @malloc(i32 8)
  store %OptVal %a1, ptr %47, align 4
  %48 = load ptr, ptr %rqs, align 8
  %49 = call %Unit @_WriteChannel(ptr %48, ptr %47)
  br label %match-cont4

tagBranch2:                                       ; preds = %rest
  %50 = load ptr, ptr %db, align 8
  %51 = call %Unit @_WriteProjection(ptr %50, i32 2)
  %52 = load ptr, ptr %rqs, align 8
  %53 = call ptr @_ReadLinearChannel(ptr %52)
  %54 = load i32, ptr %53, align 4
  %55 = call %Unit @free(ptr %53)
  %56 = call ptr @malloc(i32 4)
  store i32 %54, ptr %56, align 4
  %57 = load ptr, ptr %db, align 8
  %58 = call %Unit @_WriteChannel(ptr %57, ptr %56)
  %59 = load ptr, ptr %rqs, align 8
  %60 = call ptr @_ReadLinearChannel(ptr %59)
  %61 = load %Value, ptr %60, align 4
  %62 = call %Unit @free(ptr %60)
  %63 = call ptr @malloc(i32 4)
  store %Value %61, ptr %63, align 4
  %64 = load ptr, ptr %db, align 8
  %65 = call %Unit @_WriteChannel(ptr %64, ptr %63)
  br label %match-cont4

tagBranch3:                                       ; preds = %rest
  %66 = call i32 (ptr, ...) @printf(ptr @7)
  %67 = load ptr, ptr %db, align 8
  %68 = call %Unit @_WriteProjection(ptr %67, i32 3)
  %69 = load ptr, ptr %rqs, align 8
  %70 = call ptr @_ReadLinearChannel(ptr %69)
  %71 = load i32, ptr %70, align 4
  %72 = call %Unit @free(ptr %70)
  %73 = call ptr @malloc(i32 4)
  store i32 %71, ptr %73, align 4
  %74 = load ptr, ptr %db, align 8
  %75 = call %Unit @_WriteChannel(ptr %74, ptr %73)
  %76 = load ptr, ptr %db, align 8
  %77 = call i32 @_ReadLinearProjection(ptr %76)
  switch i32 %77, label %match-cont [
    i32 1, label %tagBranch12
    i32 2, label %tagBranch23
  ]

tagBranch12:                                      ; preds = %tagBranch3
  %78 = load ptr, ptr %rqs, align 8
  %79 = call %Unit @_WriteProjection(ptr %78, i32 1)
  %80 = load ptr, ptr %rqs, align 8
  %81 = call ptr @_ReadLinearChannel(ptr %80)
  %82 = load %Value, ptr %81, align 4
  %83 = call %Unit @free(ptr %81)
  %84 = call ptr @malloc(i32 4)
  store %Value %82, ptr %84, align 4
  %85 = load ptr, ptr %db, align 8
  %86 = call %Unit @_WriteChannel(ptr %85, ptr %84)
  br label %match-cont

tagBranch23:                                      ; preds = %tagBranch3
  %87 = load ptr, ptr %rqs, align 8
  %88 = call %Unit @_WriteProjection(ptr %87, i32 2)
  %89 = load ptr, ptr %db, align 8
  %90 = call ptr @_ReadLinearChannel(ptr %89)
  %91 = load %Value, ptr %90, align 4
  %92 = call %Unit @free(ptr %90)
  %93 = call ptr @malloc(i32 4)
  store %Value %91, ptr %93, align 4
  %94 = load ptr, ptr %rqs, align 8
  %95 = call %Unit @_WriteChannel(ptr %94, ptr %93)
  %96 = load ptr, ptr %rqs, align 8
  %97 = call ptr @_ReadLinearChannel(ptr %96)
  %98 = load %Value, ptr %97, align 4
  %99 = call %Unit @free(ptr %97)
  %100 = call ptr @malloc(i32 4)
  store %Value %98, ptr %100, align 4
  %101 = load ptr, ptr %db, align 8
  %102 = call %Unit @_WriteChannel(ptr %101, ptr %100)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch23, %tagBranch12, %tagBranch3
  br label %match-cont4

match-cont4:                                      ; preds = %match-cont, %tagBranch2, %tagBranch1, %rest
  %103 = load ptr, ptr %rqs, align 8
  %104 = call i1 @_ShouldLinearLoop(ptr %103)
  br i1 %104, label %loop, label %rest5

rest5:                                            ; preds = %match-cont4, %entry
  %105 = load ptr, ptr %setRq, align 8
  %106 = call i1 @_ShouldLinearLoop(ptr %105)
  br i1 %106, label %loop6, label %rest7

loop6:                                            ; preds = %loop6, %rest5
  %107 = load ptr, ptr %db, align 8
  %108 = call %Unit @_ContractChannel(ptr %107)
  %109 = load ptr, ptr %db, align 8
  %110 = call %Unit @_WriteProjection(ptr %109, i32 2)
  %111 = load ptr, ptr %setRq, align 8
  %112 = call ptr @_ReadLinearChannel(ptr %111)
  %113 = load i32, ptr %112, align 4
  %114 = call %Unit @free(ptr %112)
  %115 = call ptr @malloc(i32 4)
  store i32 %113, ptr %115, align 4
  %116 = load ptr, ptr %db, align 8
  %117 = call %Unit @_WriteChannel(ptr %116, ptr %115)
  %118 = load ptr, ptr %setRq, align 8
  %119 = call ptr @_ReadLinearChannel(ptr %118)
  %120 = load %Value, ptr %119, align 4
  %121 = call %Unit @free(ptr %119)
  %122 = call ptr @malloc(i32 4)
  store %Value %120, ptr %122, align 4
  %123 = load ptr, ptr %db, align 8
  %124 = call %Unit @_WriteChannel(ptr %123, ptr %122)
  %125 = load ptr, ptr %setRq, align 8
  %126 = call i1 @_ShouldLinearLoop(ptr %125)
  br i1 %126, label %loop6, label %rest7

rest7:                                            ; preds = %loop6, %rest5
  %127 = load ptr, ptr %db, align 8
  %128 = call %Unit @_WeakenChannel(ptr %127)
  %129 = call ptr @malloc(i32 4)
  store i32 0, ptr %129, align 4
  %130 = load ptr, ptr %c, align 8
  %131 = call %Unit @_WriteChannel(ptr %130, ptr %129)
  ret %Unit zeroinitializer
}

define %Unit @requests(ptr %0) {
entry:
  %v = alloca %Value, align 8
  %e.0 = alloca %Unit, align 8
  %1 = alloca %OptVal, align 8
  %v.0 = alloca %Value, align 8
  %e = alloca %Unit, align 8
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
  %14 = call i32 (ptr, ...) @printf(ptr @8)
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
  store %Unit %18, ptr %e, align 1
  %19 = call i32 (ptr, ...) @printf(ptr @9)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %20 = getelementptr %OptVal, ptr %2, i32 0, i32 1
  %21 = load %Value, ptr %20, align 4
  store %Value %21, ptr %v.0, align 4
  %22 = getelementptr %Value, ptr %v.0, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  %24 = call i32 (ptr, ...) @printf(ptr @10, i32 %23)
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
  %36 = call i32 (ptr, ...) @printf(ptr @11)
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
  store %Unit %40, ptr %e.0, align 1
  %41 = call i32 (ptr, ...) @printf(ptr @12)
  br label %match-cont5

tagBranch24:                                      ; preds = %match-cont
  %42 = getelementptr %OptVal, ptr %1, i32 0, i32 1
  %43 = load %Value, ptr %42, align 4
  store %Value %43, ptr %v, align 4
  %44 = getelementptr %Value, ptr %v, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  %46 = call i32 (ptr, ...) @printf(ptr @13, i32 %45)
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
