; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [28 x i8] c"Wrong! Got unit on server.\0A\00", align 1
@1 = private unnamed_addr constant [20 x i8] c"Correct if %u = 4!\0A\00", align 1
@2 = private unnamed_addr constant [18 x i8] c"WRONG! Got unit!\0A\00", align 1
@3 = private unnamed_addr constant [20 x i8] c"Correct if %u = 1!\0A\00", align 1
@4 = private unnamed_addr constant [18 x i8] c"Wrong! Got unit!\0A\00", align 1
@5 = private unnamed_addr constant [20 x i8] c"Correct if %u = 3!\0A\00", align 1
@6 = private unnamed_addr constant [20 x i8] c"Correct! Got unit!\0A\00", align 1
@7 = private unnamed_addr constant [25 x i8] c"Incorrect! Got int = %u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %res = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %other = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = call ptr @malloc(i32 4)
  store i32 0, ptr %3, align 4
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = call ptr @_Execute(ptr @c2)
  store ptr %6, ptr %other, align 8
  %7 = call ptr @malloc(i32 4)
  store i32 1, ptr %7, align 4
  %8 = load ptr, ptr %other, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = call ptr @malloc(i32 4)
  store i32 2, ptr %10, align 4
  %11 = load ptr, ptr %other, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  %13 = load ptr, ptr %other, align 8
  %14 = call %Unit @_PreemptChannel(ptr %13, i32 1)
  %15 = call ptr @malloc(i32 4)
  store i32 3, ptr %15, align 4
  %16 = load ptr, ptr %other, align 8
  %17 = call %Unit @_WriteChannel(ptr %16, ptr %15)
  %18 = load ptr, ptr %other, align 8
  %19 = call ptr @_ReadLossyChannel(ptr %18)
  %20 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 1, ptr %20, align 4
  %21 = icmp ne ptr %19, null
  br i1 %21, label %val-opt, label %rest

val-opt:                                          ; preds = %entry
  store i32 2, ptr %20, align 4
  %22 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %23 = load i32, ptr %19, align 4
  store i32 %23, ptr %22, align 4
  br label %rest

rest:                                             ; preds = %val-opt, %entry
  %24 = load %"(Unit + int)", ptr %2, align 4
  %25 = call %Unit @free(ptr %19)
  store %"(Unit + int)" %24, ptr %res, align 4
  %res1 = load %"(Unit + int)", ptr %res, align 4
  store %"(Unit + int)" %res1, ptr %1, align 4
  %26 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  switch i32 %27, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %rest
  %28 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %29 = load %Unit, ptr %28, align 1
  store %Unit %29, ptr %u, align 1
  %30 = call i32 (ptr, ...) @printf(ptr @0)
  br label %match-cont

tagBranch2:                                       ; preds = %rest
  %31 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %32 = load i32, ptr %31, align 4
  store i32 %32, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %33 = call i32 (ptr, ...) @printf(ptr @1, i32 %i2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %rest
  %34 = load ptr, ptr %other, align 8
  %35 = call %Unit @_PreemptChannel(ptr %34, i32 2)
  ret %Unit zeroinitializer
}

define %Unit @c2(ptr %0) {
entry:
  %i = alloca i32, align 4
  %u.1 = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %d = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %i.0 = alloca i32, align 4
  %u.0 = alloca %Unit, align 8
  %3 = alloca %"(Unit + int)", align 8
  %b = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %i.2 = alloca i32, align 4
  %u = alloca %Unit, align 8
  %5 = alloca %"(Unit + int)", align 8
  %a = alloca %"(Unit + int)", align 8
  %6 = alloca %"(Unit + int)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %7 = load ptr, ptr %c, align 8
  %8 = call ptr @_ReadLossyChannel(ptr %7)
  %9 = getelementptr %"(Unit + int)", ptr %6, i32 0, i32 0
  store i32 1, ptr %9, align 4
  %10 = icmp ne ptr %8, null
  br i1 %10, label %val-opt, label %rest

val-opt:                                          ; preds = %entry
  store i32 2, ptr %9, align 4
  %11 = getelementptr %"(Unit + int)", ptr %6, i32 0, i32 1
  %12 = load i32, ptr %8, align 4
  store i32 %12, ptr %11, align 4
  br label %rest

rest:                                             ; preds = %val-opt, %entry
  %13 = load %"(Unit + int)", ptr %6, align 4
  %14 = call %Unit @free(ptr %8)
  store %"(Unit + int)" %13, ptr %a, align 4
  %15 = load ptr, ptr %c, align 8
  %16 = call %Unit @_PreemptChannel(ptr %15, i32 1)
  %a1 = load %"(Unit + int)", ptr %a, align 4
  store %"(Unit + int)" %a1, ptr %5, align 4
  %17 = getelementptr %"(Unit + int)", ptr %5, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  switch i32 %18, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %rest
  %19 = getelementptr %"(Unit + int)", ptr %5, i32 0, i32 1
  %20 = load %Unit, ptr %19, align 1
  store %Unit %20, ptr %u, align 1
  %21 = call i32 (ptr, ...) @printf(ptr @2)
  br label %match-cont

tagBranch2:                                       ; preds = %rest
  %22 = getelementptr %"(Unit + int)", ptr %5, i32 0, i32 1
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %i.2, align 4
  %i.22 = load i32, ptr %i.2, align 4
  %24 = call i32 (ptr, ...) @printf(ptr @3, i32 %i.22)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %rest
  %25 = load ptr, ptr %c, align 8
  %26 = call ptr @_ReadLossyChannel(ptr %25)
  %27 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 1, ptr %27, align 4
  %28 = icmp ne ptr %26, null
  br i1 %28, label %val-opt3, label %rest4

val-opt3:                                         ; preds = %match-cont
  store i32 2, ptr %27, align 4
  %29 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  %30 = load i32, ptr %26, align 4
  store i32 %30, ptr %29, align 4
  br label %rest4

rest4:                                            ; preds = %val-opt3, %match-cont
  %31 = load %"(Unit + int)", ptr %4, align 4
  %32 = call %Unit @free(ptr %26)
  store %"(Unit + int)" %31, ptr %b, align 4
  %b5 = load %"(Unit + int)", ptr %b, align 4
  store %"(Unit + int)" %b5, ptr %3, align 4
  %33 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  %34 = load i32, ptr %33, align 4
  switch i32 %34, label %match-cont9 [
    i32 1, label %tagBranch16
    i32 2, label %tagBranch27
  ]

tagBranch16:                                      ; preds = %rest4
  %35 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  %36 = load %Unit, ptr %35, align 1
  store %Unit %36, ptr %u.0, align 1
  %37 = call i32 (ptr, ...) @printf(ptr @4)
  br label %match-cont9

tagBranch27:                                      ; preds = %rest4
  %38 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  %39 = load i32, ptr %38, align 4
  store i32 %39, ptr %i.0, align 4
  %i.08 = load i32, ptr %i.0, align 4
  %40 = call i32 (ptr, ...) @printf(ptr @5, i32 %i.08)
  br label %match-cont9

match-cont9:                                      ; preds = %tagBranch27, %tagBranch16, %rest4
  %41 = call ptr @malloc(i32 4)
  store i32 4, ptr %41, align 4
  %42 = load ptr, ptr %c, align 8
  %43 = call %Unit @_WriteChannel(ptr %42, ptr %41)
  %44 = load ptr, ptr %c, align 8
  %45 = call ptr @_ReadLossyChannel(ptr %44)
  %46 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 1, ptr %46, align 4
  %47 = icmp ne ptr %45, null
  br i1 %47, label %val-opt10, label %rest11

val-opt10:                                        ; preds = %match-cont9
  store i32 2, ptr %46, align 4
  %48 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %49 = load i32, ptr %45, align 4
  store i32 %49, ptr %48, align 4
  br label %rest11

rest11:                                           ; preds = %val-opt10, %match-cont9
  %50 = load %"(Unit + int)", ptr %2, align 4
  %51 = call %Unit @free(ptr %45)
  store %"(Unit + int)" %50, ptr %d, align 4
  %d12 = load %"(Unit + int)", ptr %d, align 4
  store %"(Unit + int)" %d12, ptr %1, align 4
  %52 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %53 = load i32, ptr %52, align 4
  switch i32 %53, label %match-cont16 [
    i32 1, label %tagBranch113
    i32 2, label %tagBranch214
  ]

tagBranch113:                                     ; preds = %rest11
  %54 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %55 = load %Unit, ptr %54, align 1
  store %Unit %55, ptr %u.1, align 1
  %56 = call i32 (ptr, ...) @printf(ptr @6)
  br label %match-cont16

tagBranch214:                                     ; preds = %rest11
  %57 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %58 = load i32, ptr %57, align 4
  store i32 %58, ptr %i, align 4
  %i15 = load i32, ptr %i, align 4
  %59 = call i32 (ptr, ...) @printf(ptr @7, i32 %i15)
  br label %match-cont16

match-cont16:                                     ; preds = %tagBranch214, %tagBranch113, %rest11
  %60 = load ptr, ptr %c, align 8
  %61 = call %Unit @_PreemptChannel(ptr %60, i32 2)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare %Unit @_PreemptChannel(ptr, i32)

declare ptr @_ReadLossyChannel(ptr)

declare %Unit @free(ptr)
