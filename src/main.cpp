#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>

#include "mainwindow.h"
#include <QDebug>

int main (int argc, char *argv[])
{
  KAboutData aboutData( "kparttut1", "kparttut1",
    ki18n("Terminal emulator"), "0.1",
    ki18n("A split-window terminal emulator"),
    KAboutData::License_GPL,
    ki18n("Copyright (c) 2015 Kamil Lysik") );
  KCmdLineArgs::init( argc, argv, &aboutData );

  KCmdLineOptions options;
/*
 * TODO: CmdLineOptions
Opcje:
  --profile <name>          Nazwa profilu używanego w nowej Konsoli
  --fallback-profile        Użyj wewnętrznego profilu awaryjnego
  --workdir <dir>           Ustaw początkowy katalog roboczy nowej karty lub okna na 'katalog'
  --hold, --noclose         Nie zamykaj pierwotnej sesji samoczynnie po jej zakończeniu.
  --new-tab                 Utwórz nową kartę w istniejącym oknie zamiast tworzyć nowe okno
  --tabs-from-file <file>   Twórz tabele tak, jak określono w dostarczonym pliku ustawień
  --background-mode         Uruchom konsolę w tle i przywołaj po przyciśnięciu kombinacji klawiszy Ctrl+Shift+F12 (domyślna kombinacja)
  --separate                Uruchom w osobnym procesie
  --show-menubar            Pokaż pasek menu, zastępując ustawienia domyślne
  --hide-menubar            Ukryj pasek menu, zastępując ustawienia domyślne
  --show-tabbar             Pokaż pasek kart, zastępując ustawienia domyślne
  --hide-tabbar             Ukryj pasek kart, zastępując ustawienia domyślne
  --fullscreen              Uruchom Konsole w trybie pełnego okna
  --notransparency          Wyłącz przezroczyste tła, nawet jeśli są obsługiwane przez system.
  --list-profiles           Lista dostępnych profilów
  --list-profile-properties Pokaż wszystkie nazwy właściwości profili i ich typy (do użytku z -p)
  -p <property=value>       Zmień wartość atrybutu profilu.
  -e <cmd>                  Polecenie do wykonania. Opcja ta przechwyci wszystkie następujące po niej argumenty, więc użyj jej jako ostatniej opcji.

Argumenty:
  args                      Argumenty przekazane poleceniu
*/
  //options.add("+[file]", ki18n("Document to open"));
  options.add("profile <name>", ki18n("Profile name"));
  options.add("fallback-profile", ki18n("Fallback profile name"));
  options.add("workdir <dir>", ki18n("Use cwd"));
  KCmdLineArgs::addCmdLineOptions(options);

  KApplication app;

  MainWindow* window = new MainWindow();
  window->show();

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  // You do not need to add "isSet", default value is empty string.
  //if (args->isSet("profile")) {
  //    qDebug() << "Profile" << args->getOption("profile");
  //}
  //if(args->count()){//window->load(args->url(0).url());}

  return app.exec();
}
