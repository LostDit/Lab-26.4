#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>

class Track {
    public:
        Track(const std::string& name, const std::tm& date, int duration):name(name),date(date),duration(duration) {}

    void printInfo() const  {
        std::cout<<"Название: "<<name<<std::endl;
        std::cout<<"Дата названия: "<<(date.tm_year+1900)<<"-"<<(date.tm_mon+1)<<"-"<<date.tm_mday<<std::endl;
        std::cout<<"Продолжительность: "<<duration<<" секунд"<<std::endl;
    }

    const std::string& getName() const {
        return name;
    }

    private:
        std::string name;
        std::tm date;
        int duration;
};

class Player {
public:
    void addTrack(const Track& track) {
        tracks.push_back(track);

    }

    void play() {
        if (currentState != State::Stopped) {
            std::cout << "Уже воспроизводится трек или стоит на паузе." << std::endl;
            return;

        }
        std::string trackName;
        std::cout << "Введите название трека: ";
        std::getline(std::cin, trackName);

        for (const auto& track : tracks) {
            if (track.getName() == trackName) {
                currentTrack = &track;
                currentState = State::Playing;
                std::cout << "Воспроизведение:" << std::endl;
                track.printInfo();
                return;
            }
        }
        std::cout << "Трек не найден!" << std::endl;
    }

    void pause() {
        if (currentState == State::Playing) {
            currentState = State::Paused;
            std::cout << "Пауза." << std::endl;
        } else {
            std::cout << "Невозможно поставить на паузу." << std::endl;
        }
    }

    void next() {
        if (tracks.empty()) {
            std::cout << "Нет доступных треков." << std::endl;
            return;
        }
        int index = rand() % tracks.size();
        currentTrack = &tracks[index];
        currentState = State::Playing;
        std::cout << "Переключение на следующий трек:" << std::endl;
        currentTrack->printInfo();
    }

    void stop() {
        if (currentState != State::Stopped) {
            currentState = State::Stopped;
            currentTrack = nullptr;
            std::cout << "Воспроизведение остановлено." << std::endl;
        } else {
            std::cout << "Уже остановлено." << std::endl;
        }
    }

private:
    enum class State {
        Stopped,
        Playing,
        Paused
    };

    std::vector<Track> tracks;
    const Track* currentTrack = nullptr;
    State currentState = State::Stopped;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(static_cast<unsigned>(time(nullptr)));

    Player player;

    std::tm date = {};
    date.tm_year = 124;
    date.tm_mon = 4;
    date.tm_mday = 15;
    player.addTrack(Track("Трек 1",date,300));
    player.addTrack(Track("Трек 2",date,240));
    player.addTrack(Track("Трек 3",date,180));

    std::string command;
    while (true) {
        std::cout<<"\nВведите команду (play, pause, next, stop, exit): ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }else if (command == "play") {
            player.play();
        }else if (command == "pause") {
            player.pause();
        }else if (command == "next") {
            player.next();
        }else if (command == "stop") {
            player.stop();
        }else {
            std::cout<<"Неизвестная команда!";
        }
    }

    return 0;
}