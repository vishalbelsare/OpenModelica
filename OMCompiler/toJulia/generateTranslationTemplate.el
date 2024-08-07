;; To generate files to translate using Emacs

;;TODO add more files here...
(setq util-files '(Array Autoconf  AvlSetCR AvlSetInt AvlSetPath AvlSetString AvlTreeCRToInt AvlTree AvlTreeString AvlTreeStringString BaseAvlSet BaseAvlTree BaseHashSet BaseHashTable BasePVector BaseVector ClockIndexes Config Corba Database Debug DiffAlgorithm DisjointSets DoubleEnded DynLoad ErrorExt Error ExecStat ExpandableArray File Flags FMIExt FMI GC GraphML Graph HashSetExp HashSet HashSetString HashTable2 HashTable3 HashTable4 HashTable5 HashTable6 HashTableCG HashTableCrefSimVar HashTableCrIListArray HashTableCrILst HashTableCrIntToExp HashTableCrToCrEqLst HashTableCrToExp HashTableCrToExpOption HashTableCrToExpSourceTpl HashTableCrToUnit HashTableExpToExp HashTableExpToIndexExp HashTableExpToIndex HashTable HashTablePathToFunction HashTableSimCodeEqCache HashTableSM1 HashTableStringToPath HashTableStringToProgram HashTableStringToUnit HashTableTypeToExpType HashTableUnitToString IOStreamExt IOStream JSONExt Lapack List MessagePack ModelicaExternalC Mutable Pointer Print PriorityQueue Serializer Settings SimulationResults Socket StackOverflow StringUtil System TaskGraphResults Util VarTransform ZeroMQ))

;;TODO add frontend files and NFFrontend files and so on...

(defun genLoadFileTPL (name)
  (insert
   (format
    "
      print(\"Translating %s into Julia!\\n\"); getErrorString();
      loadFile(\"Compiler/Util/%s.mo\"); getErrorString();
      writeFile(\"toJulia/toJuliaOutput/Util/%s.jl\",
      OpenModelica.Scripting.Experimental.toJulia()); getErrorString();
      deleteClass(%s); getErrorString();

   " name name name name )))

(defun generate-util-files ()
    (interactive)
    (insert
     "
     /*
     *     Automatically generated by generateTranslationTemplate.el
     *     @author Emacs
     */

     setCommandLineOptions(\"-g=MetaModelica\");getErrorString();

     ")
    (mapcar 'genLoadFileTPL util-files))
