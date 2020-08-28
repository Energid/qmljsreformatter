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
    parser.setApplicationDescription("QML/JavaScript reformatter.\n"
                                     "\n"
                                     "If destination is omitted and -i is not used, format result will be\n"
                                     "writen to standard output.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", "Source file.");
    parser.addPositionalArgument("destination", "Destination file (ignored with -i).", "[destination]");
    // A boolean option with multiple names (-i, --in-place)
    QCommandLineOption inPlaceOption(QStringList() << "i" << "in-place", "Inplace format source file.");
    parser.addOption(inPlaceOption);
#ifdef ORANGE
    // A boolean option with multiple names (-s, --split)
    QCommandLineOption splitOption(QStringList() << "s" << "split", "Split the long lines.");
    parser.addOption(splitOption);
#endif
    parser.process(app);

    const QStringList args = parser.positionalArguments();

    if (args.length() < 1) {
#ifdef ORANGE
        qWarning() << "Usage:" << argv[0] << "[-s|--split] <input-file> [<output-file>]";
        qWarning() << " or:  " << argv[0] << "[-i|--in-place] [-s|--split] <input-file>";
#else
        qWarning() << "Usage:" << argv[0] << "<input-file> [<output-file>]";
        qWarning() << " or:  " << argv[0] << "[-i|--in-place] <input-file>";
#endif
        return 1;
    }

    QString content;

    QString inputFile = args.at(0);
    QFile inFile(inputFile);
    if (inFile.open(QIODevice::ReadOnly)) {
        QTextStream ins(&inFile);
        content = ins.readAll();
        inFile.close();
    }
    else {
        qWarning() << "Error: couldn't open input file";
        return 2;
    }

    QmlJS::Document::MutablePtr doc = QmlJS::Document::create(inputFile, QmlJS::Dialect(QmlJS::Dialect::Qml));
    doc->setEditorRevision(0);
    doc->setSource(content);

    if (!doc->parse()) {
        qWarning() << "Error: doc->parse() execution";

        for (auto diagnosticMessage : doc->diagnosticMessages()) {
            qWarning("    (%d:%d) %s", diagnosticMessage.loc.startLine, diagnosticMessage.loc.startColumn, diagnosticMessage.message.toStdString().c_str());
        }

        return 3;
    }

#ifdef ORANGE
    QString formattedContent = QmlJS::reformat(doc, parser.isSet(splitOption));
#else
    QString formattedContent = QmlJS::reformat(doc);
#endif

    if (parser.isSet(inPlaceOption)) {
        if (inFile.open(QIODevice::WriteOnly)) {
            QTextStream outs(&inFile);
            outs << formattedContent;
            inFile.close();
        }
        else {
            qWarning() << "Error: couldn't reopen input file for writing";
            return 4;
        }
    }
    else if (args.length() >= 2) {
        QString outputFile = args.at(1);
        QFile outFile(outputFile);

        if (outFile.open(QIODevice::WriteOnly)) {
            QTextStream outs(&outFile);
            outs << formattedContent;
            outFile.close();
        }
        else {
            qWarning() << "Error: couldn't open output file";
            return 4;
        }
    }
    else {
        QTextStream outs(stdout);
        outs << formattedContent;
    }

    return 0;
}
