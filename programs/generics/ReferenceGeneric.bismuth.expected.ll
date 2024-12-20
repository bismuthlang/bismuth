; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"program::VVV" = type {}
%"ReferenceGeneric::Foo<boolean>" = type { i1, %"ReferenceGeneric::Bar<boolean>" }
%"ReferenceGeneric::Bar<boolean>" = type { i1 }
%"ReferenceGeneric::Foo<str>" = type { ptr, %"ReferenceGeneric::Bar<str>" }
%"ReferenceGeneric::Bar<str>" = type { ptr }

define %Unit @program(ptr %0) {
entry:
  %v = alloca %"program::VVV", align 8
  %foo2 = alloca %"ReferenceGeneric::Foo<boolean>", align 8
  %foo = alloca %"ReferenceGeneric::Foo<str>", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
