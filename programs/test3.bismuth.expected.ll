; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [10 x i8] c"Correct!\0A\00", align 1
@1 = private unnamed_addr constant [14 x i8] c"Not correct!\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = icmp slt i32 1, 2
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  %2 = call i32 (...) @printf(ptr @0)
  br label %else

else:                                             ; preds = %then, %entry
  %3 = icmp slt i32 2, 1
  br i1 %3, label %then1, label %else2

then1:                                            ; preds = %else
  %4 = call i32 (...) @printf(ptr @1)
  br label %else2

else2:                                            ; preds = %then1, %else
  %5 = sub nsw i32 0, 1
  %6 = call ptr @malloc(i32 4)
  store i32 %5, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
