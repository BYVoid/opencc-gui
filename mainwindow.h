/*
* GUI for Open Chinese Convert
*
* Created on: Jul 6, 2011
* Author: BYVoid <byvoid.kcp@gmail.com>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "converter.h"

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum Language {ENG, ZHT, ZHS};
    Ui::MainWindow *ui;
    Converter * opencc;
    QTranslator * trans;

    Language language;
    void setDefaultLanguage();
    void changeLanguage();

public slots:
    void convertSlot();
    void loadSlot();
    void saveSlot();
    void convertFileSlot();
    void aboutSlot();
    void changeLanguageToEngSlot();
    void changeLanguageToZhtSlot();
    void changeLanguageToZhsSlot();
};

#endif // MAINWINDOW_H
