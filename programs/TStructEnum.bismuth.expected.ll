; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"programs::TStructEnum::TIBB" = type { ptr, ptr }
%"programs::TStructEnum::ETIBBOB" = type { i32, [16 x i8] }

@0 = private unnamed_addr constant [25 x i8] c"%s = {b1 : %u, b2 : %u}\0A\00", align 1
@1 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@4 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@5 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@6 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@7 = private unnamed_addr constant [8 x i8] c"------\0A\00", align 1
@8 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@9 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@10 = private unnamed_addr constant [13 x i8] c"b (orig/9;9)\00", align 1

define %Unit @"programs::TStructEnum::printTIBB"(ptr %0, %"programs::TStructEnum::TIBB" %1) {
entry:
  %b = alloca %"programs::TStructEnum::TIBB", align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store %"programs::TStructEnum::TIBB" %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %2 = getelementptr %"programs::TStructEnum::TIBB", ptr %b, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = load i32, ptr %4, align 4
  %6 = getelementptr %"programs::TStructEnum::TIBB", ptr %b, i32 0, i32 1
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1, i32 %5, i32 %9)
  ret %Unit zeroinitializer
}

define %Unit @"programs::TStructEnum::foo"(ptr %0) {
entry:
  %t.0 = alloca i32, align 4
  %i = alloca i32, align 4
  %t = alloca i32, align 4
  %iPtr = alloca %"programs::TStructEnum::TIBB", align 8
  %1 = alloca %"programs::TStructEnum::ETIBBOB", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load %"programs::TStructEnum::ETIBBOB", ptr %3, align 4
  %5 = call %Unit @free(ptr %3)
  store %"programs::TStructEnum::ETIBBOB" %4, ptr %1, align 4
  %6 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %1, i32 0, i32 0
  %7 = load %"programs::TStructEnum::ETIBBOB", ptr %6, align 4
  switch %"programs::TStructEnum::ETIBBOB" %7, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %8 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %1, i32 0, i32 1
  %9 = load %"programs::TStructEnum::TIBB", ptr %8, align 8
  store %"programs::TStructEnum::TIBB" %9, ptr %iPtr, align 8
  %iPtr1 = load %"programs::TStructEnum::TIBB", ptr %iPtr, align 8
  %10 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @1, %"programs::TStructEnum::TIBB" %iPtr1)
  %11 = getelementptr %"programs::TStructEnum::TIBB", ptr %iPtr, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = load ptr, ptr %12, align 8
  store i32 7, ptr %13, align 4
  %iPtr2 = load %"programs::TStructEnum::TIBB", ptr %iPtr, align 8
  %14 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @2, %"programs::TStructEnum::TIBB" %iPtr2)
  %15 = sub nsw i32 0, 1
  %16 = call ptr @malloc(i32 4)
  store i32 %15, ptr %16, align 4
  %17 = load ptr, ptr %c, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  %19 = load ptr, ptr %c, align 8
  %20 = call ptr @_ReadLinearChannel(ptr %19)
  %21 = load i32, ptr %20, align 4
  %22 = call %Unit @free(ptr %20)
  store i32 %21, ptr %t, align 4
  %iPtr3 = load %"programs::TStructEnum::TIBB", ptr %iPtr, align 8
  %23 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @3, %"programs::TStructEnum::TIBB" %iPtr3)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %24 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %1, i32 0, i32 1
  %25 = load i32, ptr %24, align 4
  store i32 %25, ptr %i, align 4
  %26 = sub nsw i32 0, 1
  %27 = call ptr @malloc(i32 4)
  store i32 %26, ptr %27, align 4
  %28 = load ptr, ptr %c, align 8
  %29 = call %Unit @_WriteChannel(ptr %28, ptr %27)
  %30 = load ptr, ptr %c, align 8
  %31 = call ptr @_ReadLinearChannel(ptr %30)
  %32 = load i32, ptr %31, align 4
  %33 = call %Unit @free(ptr %31)
  store i32 %32, ptr %t.0, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u.0 = alloca i32, align 4
  %toSend.0 = alloca %"programs::TStructEnum::ETIBBOB", align 8
  %tibb.0 = alloca %"programs::TStructEnum::TIBB", align 8
  %1 = alloca %"programs::TStructEnum::TIBB", align 8
  %shared.0 = alloca ptr, align 8
  %a.0 = alloca ptr, align 8
  %u = alloca i32, align 4
  %toSend = alloca %"programs::TStructEnum::ETIBBOB", align 8
  %tibb = alloca %"programs::TStructEnum::TIBB", align 8
  %2 = alloca %"programs::TStructEnum::TIBB", align 8
  %shared = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = call ptr @_Execute(ptr @"programs::TStructEnum::foo")
  store ptr %3, ptr %a, align 8
  %4 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %4, align 4
  %5 = call ptr @GC_malloc(i64 8)
  store ptr %4, ptr %5, align 8
  store ptr %5, ptr %shared, align 8
  %shared1 = load ptr, ptr %shared, align 8
  %6 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %6, align 4
  %7 = call ptr @GC_malloc(i64 8)
  store ptr %6, ptr %7, align 8
  %8 = getelementptr %"programs::TStructEnum::TIBB", ptr %2, i32 0, i32 0
  store ptr %shared1, ptr %8, align 8
  %9 = getelementptr %"programs::TStructEnum::TIBB", ptr %2, i32 0, i32 1
  store ptr %7, ptr %9, align 8
  %10 = load %"programs::TStructEnum::TIBB", ptr %2, align 8
  store %"programs::TStructEnum::TIBB" %10, ptr %tibb, align 8
  %tibb2 = load %"programs::TStructEnum::TIBB", ptr %tibb, align 8
  %11 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %toSend, i32 0, i32 0
  store i32 1, ptr %11, align 4
  %12 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %toSend, i32 0, i32 1
  store %"programs::TStructEnum::TIBB" %tibb2, ptr %12, align 8
  %tibb3 = load %"programs::TStructEnum::TIBB", ptr %tibb, align 8
  %13 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @4, %"programs::TStructEnum::TIBB" %tibb3)
  %toSend4 = load %"programs::TStructEnum::ETIBBOB", ptr %toSend, align 4
  %14 = call ptr @_address_map_create()
  %15 = call %"programs::TStructEnum::ETIBBOB" @_clone_ETIBBOB(%"programs::TStructEnum::ETIBBOB" %toSend4, ptr %14)
  %16 = call %Unit @_address_map_delete(ptr %14)
  %17 = call ptr @malloc(i32 20)
  store %"programs::TStructEnum::ETIBBOB" %15, ptr %17, align 4
  %18 = load ptr, ptr %a, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  %20 = load ptr, ptr %a, align 8
  %21 = call ptr @_ReadLinearChannel(ptr %20)
  %22 = load i32, ptr %21, align 4
  %23 = call %Unit @free(ptr %21)
  store i32 %22, ptr %u, align 4
  %tibb5 = load %"programs::TStructEnum::TIBB", ptr %tibb, align 8
  %24 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @5, %"programs::TStructEnum::TIBB" %tibb5)
  %shared6 = load ptr, ptr %shared, align 8
  %25 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %25, align 4
  store ptr %25, ptr %shared6, align 8
  %tibb7 = load %"programs::TStructEnum::TIBB", ptr %tibb, align 8
  %26 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @6, %"programs::TStructEnum::TIBB" %tibb7)
  %27 = sub nsw i32 0, 1
  %28 = call ptr @malloc(i32 4)
  store i32 %27, ptr %28, align 4
  %29 = load ptr, ptr %a, align 8
  %30 = call %Unit @_WriteChannel(ptr %29, ptr %28)
  %31 = call %Unit (ptr, ...) @printf(ptr @7)
  %32 = call ptr @_Execute(ptr @"programs::TStructEnum::foo")
  store ptr %32, ptr %a.0, align 8
  %33 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %33, align 4
  %34 = call ptr @GC_malloc(i64 8)
  store ptr %33, ptr %34, align 8
  store ptr %34, ptr %shared.0, align 8
  %shared.08 = load ptr, ptr %shared.0, align 8
  %shared.09 = load ptr, ptr %shared.0, align 8
  %35 = getelementptr %"programs::TStructEnum::TIBB", ptr %1, i32 0, i32 0
  store ptr %shared.08, ptr %35, align 8
  %36 = getelementptr %"programs::TStructEnum::TIBB", ptr %1, i32 0, i32 1
  store ptr %shared.09, ptr %36, align 8
  %37 = load %"programs::TStructEnum::TIBB", ptr %1, align 8
  store %"programs::TStructEnum::TIBB" %37, ptr %tibb.0, align 8
  %tibb.010 = load %"programs::TStructEnum::TIBB", ptr %tibb.0, align 8
  %38 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %toSend.0, i32 0, i32 0
  store i32 1, ptr %38, align 4
  %39 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %toSend.0, i32 0, i32 1
  store %"programs::TStructEnum::TIBB" %tibb.010, ptr %39, align 8
  %tibb.011 = load %"programs::TStructEnum::TIBB", ptr %tibb.0, align 8
  %40 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @8, %"programs::TStructEnum::TIBB" %tibb.011)
  %toSend.012 = load %"programs::TStructEnum::ETIBBOB", ptr %toSend.0, align 4
  %41 = call ptr @_address_map_create()
  %42 = call %"programs::TStructEnum::ETIBBOB" @_clone_ETIBBOB(%"programs::TStructEnum::ETIBBOB" %toSend.012, ptr %41)
  %43 = call %Unit @_address_map_delete(ptr %41)
  %44 = call ptr @malloc(i32 20)
  store %"programs::TStructEnum::ETIBBOB" %42, ptr %44, align 4
  %45 = load ptr, ptr %a.0, align 8
  %46 = call %Unit @_WriteChannel(ptr %45, ptr %44)
  %47 = load ptr, ptr %a.0, align 8
  %48 = call ptr @_ReadLinearChannel(ptr %47)
  %49 = load i32, ptr %48, align 4
  %50 = call %Unit @free(ptr %48)
  store i32 %49, ptr %u.0, align 4
  %tibb.013 = load %"programs::TStructEnum::TIBB", ptr %tibb.0, align 8
  %51 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @9, %"programs::TStructEnum::TIBB" %tibb.013)
  %shared.014 = load ptr, ptr %shared.0, align 8
  %52 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %52, align 4
  store ptr %52, ptr %shared.014, align 8
  %tibb.015 = load %"programs::TStructEnum::TIBB", ptr %tibb.0, align 8
  %53 = call %Unit @"programs::TStructEnum::printTIBB"(ptr @10, %"programs::TStructEnum::TIBB" %tibb.015)
  %54 = sub nsw i32 0, 1
  %55 = call ptr @malloc(i32 4)
  store i32 %54, ptr %55, align 4
  %56 = load ptr, ptr %a.0, align 8
  %57 = call %Unit @_WriteChannel(ptr %56, ptr %55)
  %58 = call ptr @malloc(i32 4)
  store i32 0, ptr %58, align 4
  %59 = load ptr, ptr %c, align 8
  %60 = call %Unit @_WriteChannel(ptr %59, ptr %58)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare ptr @GC_malloc(i64)

declare ptr @_address_map_create()

define private %"programs::TStructEnum::ETIBBOB" @_clone_ETIBBOB(%"programs::TStructEnum::ETIBBOB" %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %"programs::TStructEnum::ETIBBOB", align 8
  store %"programs::TStructEnum::ETIBBOB" %0, ptr %v, align 4
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %v, i32 0, i32 1
  %3 = getelementptr %"programs::TStructEnum::ETIBBOB", ptr %v, i32 0, i32 0
  %4 = load ptr, ptr %3, align 8
  switch ptr %4, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %5 = load %"programs::TStructEnum::TIBB", ptr %2, align 8
  %6 = load ptr, ptr %m, align 8
  %7 = call %"programs::TStructEnum::TIBB" @_clone_TIBB(%"programs::TStructEnum::TIBB" %5, ptr %6)
  store %"programs::TStructEnum::TIBB" %7, ptr %2, align 8
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %8 = load i32, ptr %2, align 4
  %9 = load ptr, ptr %m, align 8
  store i32 %8, ptr %2, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %10 = load %"programs::TStructEnum::ETIBBOB", ptr %v, align 4
  ret %"programs::TStructEnum::ETIBBOB" %10
}

define private %"programs::TStructEnum::TIBB" @_clone_TIBB(%"programs::TStructEnum::TIBB" %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %"programs::TStructEnum::TIBB", align 8
  store %"programs::TStructEnum::TIBB" %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %"programs::TStructEnum::TIBB", ptr %v, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %m, align 8
  %5 = call ptr @"_clone_Box<Box<int>>"(ptr %3, ptr %4)
  store ptr %5, ptr %2, align 8
  %6 = getelementptr %"programs::TStructEnum::TIBB", ptr %v, i32 0, i32 1
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @"_clone_Box<Box<int>>"(ptr %7, ptr %8)
  store ptr %9, ptr %6, align 8
  %10 = load %"programs::TStructEnum::TIBB", ptr %v, align 8
  ret %"programs::TStructEnum::TIBB" %10
}

define private ptr @"_clone_Box<Box<int>>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = call ptr @"_clone_Box<int>"(ptr %8, ptr %6)
  %10 = call ptr @GC_malloc(i64 8)
  store ptr %9, ptr %10, align 8
  %11 = load ptr, ptr %m, align 8
  %12 = call %Unit @_address_map_put(ptr %11, ptr %2, ptr %10)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %10, %else ]
  ret ptr %phi
}

declare ptr @_address_map_has(ptr, ptr)

define private ptr @"_clone_Box<int>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load i32, ptr %7, align 4
  %9 = call ptr @GC_malloc(i64 8)
  store i32 %8, ptr %9, align 4
  %10 = load ptr, ptr %m, align 8
  %11 = call %Unit @_address_map_put(ptr %10, ptr %2, ptr %9)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %9, %else ]
  ret ptr %phi
}

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
