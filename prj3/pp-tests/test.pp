BEGIN PROGRAM@<unknown>:1:0
  BEGIN CLASS@test.decaf:1:6 [C:Object]
    BEGIN FIELD@test.decaf:2:2 [isStatic=false, access=PUBLIC]
      TYPE@test.decaf:2:2 [int]
      INIT_DECLARATOR@test.decaf:2:6 [a]
        NIL_EXP@test.decaf:2:6
    END FIELD@test.decaf:2:2 [isStatic=false, access=PUBLIC]
    BEGIN FIELD@test.decaf:3:9 [isStatic=true, access=PUBLIC]
      TYPE@test.decaf:3:9 [boolean[]]
      INIT_DECLARATOR@test.decaf:3:19 [a]
        NIL_EXP@test.decaf:3:19
      INIT_DECLARATOR@test.decaf:3:22 [b[]]
        NIL_EXP@test.decaf:3:22
    END FIELD@test.decaf:3:9 [isStatic=true, access=PUBLIC]
    BEGIN METHOD@test.decaf:5:17 [f: isStatic=true, access=PUBLIC]
      TYPE@test.decaf:5:9 [boolean]
      BEGIN BLOCK@test.decaf:5:21
      END BLOCK@test.decaf:5:21
    END METHOD@test.decaf:5:17 [f: isStatic=true, access=PUBLIC]
    BEGIN METHOD@test.decaf:7:7 [f: isStatic=false, access=PUBLIC]
      TYPE@test.decaf:7:2 [void]
      BEGIN BLOCK@test.decaf:7:11
        VAR_DEC@test.decaf:8:4
          TYPE@test.decaf:8:4 [boolean[]]
          INIT_DECLARATOR@test.decaf:8:14 [a]
            NIL_EXP@test.decaf:8:14
          INIT_DECLARATOR@test.decaf:8:17 [b[]]
            NIL_EXP@test.decaf:8:17
        EXP@test.decaf:9:6
          ASSIGN@test.decaf:9:6
            NAME@test.decaf:9:4 [a]
            ACCESS@test.decaf:9:11
              ACCESS@test.decaf:9:9
                NAME@test.decaf:9:8 [a]
                NAME@test.decaf:9:10 [b]
              NAME@test.decaf:9:12 [c]
        EXP@test.decaf:10:22
          ASSIGN@test.decaf:10:22
            ACCESS@test.decaf:10:11
              ACCESS@test.decaf:10:5
                NAME@test.decaf:10:4 [b]
                CALL@test.decaf:10:6 [c]
                  NAME@test.decaf:10:8 [a1]
              CALL@test.decaf:10:12 [f]
                NAME@test.decaf:10:14 [a2]
                LITERAL@test.decaf:10:18 [23: INT]
            NAME@test.decaf:10:24 [x]
      END BLOCK@test.decaf:7:11
    END METHOD@test.decaf:7:7 [f: isStatic=false, access=PUBLIC]
  END CLASS@test.decaf:1:6 [C:Object]
END PROGRAM@<unknown>:1:0
