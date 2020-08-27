cmake_minimum_required(VERSION 3.6)

project(qmljsreformatter)

find_package(Qt5 REQUIRED CONFIG COMPONENTS Widgets Xml)

if (NOT ((TARGET Qt5::Widgets) 
         AND (${Qt5Widgets_VERSION_MAJOR} EQUAL 5) 
         AND (${Qt5Widgets_VERSION_MINOR} EQUAL 12)))
    return()
endif()

set(qtCreatorSrc "qt-creator-simplified/src/libs")

add_executable(${PROJECT_NAME}
    ${qtCreatorSrc}/cplusplus/cppmodelmanagerbase.h
    ${qtCreatorSrc}/utils/filesystemwatcher.h
    ${qtCreatorSrc}/utils/globalfilechangeblocker.h
    ${qtCreatorSrc}/utils/savefile.h
    ${qtCreatorSrc}/utils/optional.h
    ${qtCreatorSrc}/utils/qtcprocess.h
    ${qtCreatorSrc}/qmljs/qmljscodeformatter.h
    ${qtCreatorSrc}/qmljs/qmljsinterpreter.h
    ${qtCreatorSrc}/qmljs/qmljsmodelmanagerinterface.h
    ${qtCreatorSrc}/qmljs/qmljsplugindumper.h
    ${qtCreatorSrc}/qmljs/qmljsreformatter.h
    ${qtCreatorSrc}/3rdparty/cplusplus/AST.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ASTClone.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ASTMatch0.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ASTMatcher.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ASTVisit.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ASTVisitor.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Bind.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Control.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/CoreTypes.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/DiagnosticClient.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/FullySpecifiedType.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Keywords.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Lexer.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Literals.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Matcher.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/MemoryPool.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Name.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Names.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/NameVisitor.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ObjectiveCAtKeywords.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/ObjectiveCTypeQualifiers.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Parser.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/QtContextKeywords.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/SafeMatcher.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Scope.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Symbol.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Symbols.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Templates.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Token.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/TranslationUnit.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/Type.cpp
    ${qtCreatorSrc}/3rdparty/cplusplus/TypeVisitor.cpp
    ${qtCreatorSrc}/cplusplus/CppDocument.cpp
    ${qtCreatorSrc}/cplusplus/cppmodelmanagerbase.cpp
    ${qtCreatorSrc}/cplusplus/CppRewriter.cpp
    ${qtCreatorSrc}/cplusplus/DependencyTable.cpp
    ${qtCreatorSrc}/cplusplus/DeprecatedGenTemplateInstance.cpp
    ${qtCreatorSrc}/cplusplus/FastPreprocessor.cpp
    ${qtCreatorSrc}/cplusplus/LookupContext.cpp
    ${qtCreatorSrc}/cplusplus/LookupItem.cpp
    ${qtCreatorSrc}/cplusplus/Macro.cpp
    ${qtCreatorSrc}/cplusplus/NamePrettyPrinter.cpp
    ${qtCreatorSrc}/cplusplus/Overview.cpp
    ${qtCreatorSrc}/cplusplus/pp-engine.cpp
    ${qtCreatorSrc}/cplusplus/PPToken.cpp
    ${qtCreatorSrc}/cplusplus/PreprocessorClient.cpp
    ${qtCreatorSrc}/cplusplus/PreprocessorEnvironment.cpp
    ${qtCreatorSrc}/cplusplus/ResolveExpression.cpp
    ${qtCreatorSrc}/cplusplus/TypeOfExpression.cpp
    ${qtCreatorSrc}/cplusplus/TypePrettyPrinter.cpp
    ${qtCreatorSrc}/utils/environment.cpp
    ${qtCreatorSrc}/utils/fileutils.cpp
    ${qtCreatorSrc}/utils/filesystemwatcher.cpp
    ${qtCreatorSrc}/utils/globalfilechangeblocker.cpp
    ${qtCreatorSrc}/utils/hostosinfo.cpp
    ${qtCreatorSrc}/utils/json.cpp
    ${qtCreatorSrc}/utils/qrcparser.cpp
    ${qtCreatorSrc}/utils/qtcassert.cpp
    ${qtCreatorSrc}/utils/runextensions.cpp
    ${qtCreatorSrc}/utils/namevaluedictionary.cpp
    ${qtCreatorSrc}/utils/namevalueitem.cpp
    ${qtCreatorSrc}/utils/qtcprocess.cpp
    ${qtCreatorSrc}/utils/savefile.cpp
    ${qtCreatorSrc}/languageutils/componentversion.cpp
    ${qtCreatorSrc}/languageutils/fakemetaobject.cpp
    ${qtCreatorSrc}/qmljs/parser/qmlerror.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljsast.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljsastvisitor.cpp
    ${qtCreatorSrc}/qmljs/parser/qmldirparser.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljsengine_p.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljsgrammar.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljslexer.cpp
    ${qtCreatorSrc}/qmljs/parser/qmljsparser.cpp
    ${qtCreatorSrc}/qmljs/persistenttrie.cpp
    ${qtCreatorSrc}/qmljs/qmljsbind.cpp
    ${qtCreatorSrc}/qmljs/qmljsbundle.cpp
    ${qtCreatorSrc}/qmljs/qmljscodeformatter.cpp
    ${qtCreatorSrc}/qmljs/qmljscontext.cpp
    ${qtCreatorSrc}/qmljs/qmljsdialect.cpp
    ${qtCreatorSrc}/qmljs/qmljsdocument.cpp
    ${qtCreatorSrc}/qmljs/qmljsevaluate.cpp
    ${qtCreatorSrc}/qmljs/qmljsfindexportedcpptypes.cpp
    ${qtCreatorSrc}/qmljs/qmljsimportdependencies.cpp
    ${qtCreatorSrc}/qmljs/qmljsinterpreter.cpp
    ${qtCreatorSrc}/qmljs/qmljsmodelmanagerinterface.cpp
    ${qtCreatorSrc}/qmljs/qmljsplugindumper.cpp
    ${qtCreatorSrc}/qmljs/qmljsreformatter.cpp
    ${qtCreatorSrc}/qmljs/qmljsscanner.cpp
    ${qtCreatorSrc}/qmljs/qmljsscopeastpath.cpp
    ${qtCreatorSrc}/qmljs/qmljsscopebuilder.cpp
    ${qtCreatorSrc}/qmljs/qmljsscopechain.cpp
    ${qtCreatorSrc}/qmljs/qmljstypedescriptionreader.cpp
    ${qtCreatorSrc}/qmljs/qmljsutils.cpp
    ${qtCreatorSrc}/qmljs/qmljsvalueowner.cpp
    ${qtCreatorSrc}/qmljs/qmljsviewercontext.cpp
    src/main.cpp
)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt5::Widgets
    Qt5::Xml
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    QT_CREATOR
    CPLUSPLUS_BUILD_STATIC_LIB
    QML_BUILD_STATIC_LIB
    LANGUAGEUTILS_BUILD_STATIC_LIB
    QTCREATOR_UTILS_STATIC_LIB
    UNICODE
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${qtCreatorSrc}
    ${qtCreatorSrc}/3rdparty
)

install(TARGETS ${PROJECT_NAME})
