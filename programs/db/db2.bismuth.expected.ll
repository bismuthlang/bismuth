; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + Value)" = type { i32, [4 x i8] }
%Value = type { i32 }

define %Unit @Database(ptr %0) {
entry:
  %key = alloca i32, align 4
  %1 = alloca %"(Unit + Value)", align 8
  %2 = alloca %"(Unit + Value)", align 8
  %k = alloca i32, align 4
  %data = alloca [10 x %Value], align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call i1 @_ShouldLinearLoop(ptr %3)
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %5 = load ptr, ptr %c, align 8
  %6 = call i32 @_ReadLinearProjection(ptr %5)
  switch i32 %6, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
  ]

tagBranch1:                                       ; preds = %loop
  %7 = load ptr, ptr %c, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %k, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %loop
  %11 = load ptr, ptr %c, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i32, ptr %12, align 4
  %14 = call %Unit @free(ptr %12)
  %15 = icmp slt i32 %13, 10
  br i1 %15, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %tagBranch2
  %16 = icmp sge i32 %13, 0
  br i1 %16, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %17 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %13
  %18 = load %Value, ptr %17, align 4
  %19 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 0
  store i32 2, ptr %19, align 4
  %20 = getelementptr %"(Unit + Value)", ptr %2, i32 0, i32 1
  store %Value %18, ptr %20, align 4
  %21 = load %"(Unit + Value)", ptr %2, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %tagBranch2
  %22 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 0
  store i32 1, ptr %22, align 4
  %23 = getelementptr %"(Unit + Value)", ptr %1, i32 0, i32 1
  store %Unit zeroinitializer, ptr %23, align 1
  %24 = load %"(Unit + Value)", ptr %1, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + Value)" [ %21, %accessGTZ ], [ %24, %accessBad ]
  %25 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %arrayAccess, ptr %25, align 4
  %26 = load ptr, ptr %c, align 8
  %27 = call %Unit @_WriteChannel(ptr %26, ptr %25)
  br label %match-cont

tagBranch3:                                       ; preds = %loop
  %28 = load ptr, ptr %c, align 8
  %29 = call ptr @_ReadLinearChannel(ptr %28)
  %30 = load i32, ptr %29, align 4
  %31 = call %Unit @free(ptr %29)
  store i32 %30, ptr %key, align 4
  %key1 = load i32, ptr %key, align 4
  %32 = getelementptr [10 x %Value], ptr %data, i32 0, i32 %key1
  %33 = load ptr, ptr %c, align 8
  %34 = call ptr @_ReadLinearChannel(ptr %33)
  %35 = load %Value, ptr %34, align 4
  %36 = call %Unit @free(ptr %34)
  store %Value %35, ptr %32, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %accessAfter, %tagBranch1, %loop
  %37 = load ptr, ptr %c, align 8
  %38 = call i1 @_ShouldLinearLoop(ptr %37)
  br i1 %38, label %loop, label %rest

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
  br label %match-cont

tagBranch2:                                       ; preds = %loop1
  %41 = load ptr, ptr %db, align 8
  %42 = call %Unit @_WriteProjection(ptr %41, i32 2)
  %43 = load ptr, ptr %rqs, align 8
  %44 = call ptr @_ReadLinearChannel(ptr %43)
  %45 = load i32, ptr %44, align 4
  %46 = call %Unit @free(ptr %44)
  %47 = call ptr @malloc(i32 4)
  store i32 %45, ptr %47, align 4
  %48 = load ptr, ptr %db, align 8
  %49 = call %Unit @_WriteChannel(ptr %48, ptr %47)
  %50 = load ptr, ptr %db, align 8
  %51 = call ptr @_ReadLinearChannel(ptr %50)
  %52 = load %"(Unit + Value)", ptr %51, align 4
  %53 = call %Unit @free(ptr %51)
  store %"(Unit + Value)" %52, ptr %a, align 4
  %a2 = load %"(Unit + Value)", ptr %a, align 4
  %54 = call ptr @malloc(i32 8)
  store %"(Unit + Value)" %a2, ptr %54, align 4
  %55 = load ptr, ptr %rqs, align 8
  %56 = call %Unit @_WriteChannel(ptr %55, ptr %54)
  br label %match-cont

tagBranch3:                                       ; preds = %loop1
  %57 = load ptr, ptr %db, align 8
  %58 = call %Unit @_WriteProjection(ptr %57, i32 3)
  %59 = load ptr, ptr %rqs, align 8
  %60 = call ptr @_ReadLinearChannel(ptr %59)
  %61 = load i32, ptr %60, align 4
  %62 = call %Unit @free(ptr %60)
  %63 = call ptr @malloc(i32 4)
  store i32 %61, ptr %63, align 4
  %64 = load ptr, ptr %db, align 8
  %65 = call %Unit @_WriteChannel(ptr %64, ptr %63)
  %66 = load ptr, ptr %rqs, align 8
  %67 = call ptr @_ReadLinearChannel(ptr %66)
  %68 = load %Value, ptr %67, align 4
  %69 = call %Unit @free(ptr %67)
  %70 = call ptr @malloc(i32 4)
  store %Value %68, ptr %70, align 4
  %71 = load ptr, ptr %db, align 8
  %72 = call %Unit @_WriteChannel(ptr %71, ptr %70)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch3, %tagBranch2, %tagBranch1, %loop1
  %73 = load ptr, ptr %rqs, align 8
  %74 = call i1 @_ShouldLinearLoop(ptr %73)
  br i1 %74, label %loop1, label %rest3

rest3:                                            ; preds = %match-cont, %rest
  %75 = load ptr, ptr %db, align 8
  %76 = call %Unit @_WeakenChannel(ptr %75)
  %77 = call ptr @malloc(i32 4)
  store i32 0, ptr %77, align 4
  %78 = load ptr, ptr %c, align 8
  %79 = call %Unit @_WriteChannel(ptr %78, ptr %77)
  ret %Unit zeroinitializer
}

define %Unit @requests(ptr %0) {
entry:
  %opt = alloca %"(Unit + Value)", align 8
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
  %10 = load %"(Unit + Value)", ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  store %"(Unit + Value)" %10, ptr %opt, align 4
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
