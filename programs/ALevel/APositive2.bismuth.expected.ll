; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %result = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 @getIntArg(i32 1)
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp slt i32 %i1, 0
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  %3 = sub nsw i32 0, 1
  store i32 %3, ptr %result, align 4
  br label %if-cont5

else:                                             ; preds = %entry
  %i2 = load i32, ptr %i, align 4
  %4 = icmp sgt i32 %i2, 0
  br i1 %4, label %then3, label %else4

then3:                                            ; preds = %else
  store i32 1, ptr %result, align 4
  br label %if-cont

else4:                                            ; preds = %else
  store i32 0, ptr %result, align 4
  br label %if-cont

if-cont:                                          ; preds = %else4, %then3
  br label %if-cont5

if-cont5:                                         ; preds = %if-cont, %then
  %result6 = load i32, ptr %result, align 4
  %5 = call ptr @malloc(i32 4)
  store i32 %result6, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer
}

declare i32 @getIntArg(i32)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
