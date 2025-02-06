; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [6 x i8] c"true\0A\00", align 1
@1 = private unnamed_addr constant [7 x i8] c"false\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %test = alloca i1, align 1
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = sub nsw i32 0, 1
  store i32 %1, ptr %a, align 4
  store i32 20, ptr %b, align 4
  %a1 = load i32, ptr %a, align 4
  %2 = icmp sgt i32 %a1, 0
  br i1 %2, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %entry
  %b2 = load i32, ptr %b, align 4
  %3 = icmp eq i32 %b2, 2
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %entry
  %logAnd = phi i1 [ %2, %entry ], [ %3, %prevTrueAnd ]
  store i1 %logAnd, ptr %test, align 1
  %test3 = load i1, ptr %test, align 1
  br i1 %test3, label %then, label %else

then:                                             ; preds = %mergeBlkAnd
  %4 = call i32 (ptr, ...) @printf(ptr @0)
  br label %if-cont

else:                                             ; preds = %mergeBlkAnd
  %5 = call i32 (ptr, ...) @printf(ptr @1)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %6 = call ptr @malloc(i32 4)
  store i32 0, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
