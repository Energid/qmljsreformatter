/*
 * Copyright (C) 2017 - 2019 Orange
 *
 * This software is distributed under the terms and conditions of the GNU
 * General Public Licence version 3 as published by the Free Software
 * Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
 * included in the packaging of this file. Please review the following
 * information to ensure the GNU General Public License requirements will
 * be met: https://www.gnu.org/licenses/gpl-3.0.html.
 */

/*
 * Orange version of the Qt Creator's qmljsreformatter
 *
 * Create a qmljsreformatter binary from the modified sources of Qt Creator.
 *
 * Version:     1.0
 * Created:     2017-04-03 by Julien Déramond
 */

#include <QCommandLineParser>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <cstdio>

#ifdef ORANGE
#include "qmljsreformatter.h"
#else
#include "qmljs/qmljsreformatter.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("qmljsreformatter");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("A tool to update QML/JavaScript code to match QtCreator format.\n"
                                     "\n"
                                     "If no arguments are specified, it formats the code from standard input\n"
                                     "and writes the result to the standard output.\n"
                                     "If <file>s are given, it reformats the files. If -i is specified\n"
                                     "together with <file>s, the files are edited in-place. Otherwise, the\n"
                                     "result is written to the standard output.");
    parser.addHelpOption();
    parser.addVersionOption();
    // A boolean option with multiple names (-i, --in-place)
    QCommandLineOption inPlaceOption(QStringList() << "i" << "in-place", "Inplace format source file.");
    parser.addOption(inPlaceOption);
#ifdef ORANGE
    // A boolean option with multiple names (-s, --split)
    QCommandLineOption splitOption(QStringList() << "s" << "split", "Split the long lines.");
    parser.addOption(splitOption);
#endif
    parser.process(app);

    QStringList args = parser.positionalArguments();
    if (args.isEmpty()) {
        args.append("/dev/stdin");
    }

    for (int ii = 0; ii < args.length(); ++ii) {
        QString content;

        QString inputFile = args.at(ii);
        if (inputFile == "/dev/stdin") {
            if (!parser.isSet(inPlaceOption)) {
                QFile inFile(inputFile);
                if (inFile.open(QIODevice::ReadOnly)) {
                    QTextStream ins(stdin);
                    content = ins.readAll();
                }
            }
            else {
                qWarning() << "Error: cannot use -i when reading from stdin";
                return 1;
            }
        }
        else {
            QFile inFile(inputFile);
            if (inFile.open(QIODevice::ReadOnly)) {
                QTextStream ins(&inFile);
                content = ins.readAll();
                inFile.close();
            }
            else {
                qWarning().nospace().noquote() << "Error: couldn't open input file '" << inputFile << "'";
                return 1;
            }
        }

        QmlJS::Document::MutablePtr doc = QmlJS::Document::create(inputFile, QmlJS::Dialect(QmlJS::Dialect::Qml));
        doc->setEditorRevision(0);
        doc->setSource(content);

        if (!doc->parse()) {
            qWarning().nospace().noquote() << "Error: doc->parse() execution within '" << inputFile << "'";

            for (auto diagnosticMessage : doc->diagnosticMessages()) {
                qWarning("    (%d:%d) %s", diagnosticMessage.loc.startLine, diagnosticMessage.loc.startColumn, diagnosticMessage.message.toStdString().c_str());
            }

            return 2;
        }

#ifdef ORANGE
        QString formattedContent = QmlJS::reformat(doc, parser.isSet(splitOption));
#else
        QString formattedContent = QmlJS::reformat(doc);
#endif

        if (parser.isSet(inPlaceOption)) {
            QFile inFile(inputFile);
            if (inFile.open(QIODevice::WriteOnly)) {
                QTextStream outs(&inFile);
                outs << formattedContent;
                inFile.close();
            }
            else {
                qWarning().nospace().noquote() << "Error: couldn't reopen input file '" << inputFile << "' for writing";
                return 3;
            }
        }
        else {
            QTextStream outs(stdout);
            outs << formattedContent;
        }
    }

    return 0;
}
