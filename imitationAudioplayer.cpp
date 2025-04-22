#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <random>

class Track {
public:
    std::string name;
    std::tm date;
    int duration;

    Track(const std::string& name, const std::tm& date, int duration)
        : name(name), date(date), duration(duration) {}
};

class Player {
private:
    std::vector<Track> tracks;
    Track* currentTrack;
    bool isPlaying;
    bool isPaused;

public:
    Player() : currentTrack(nullptr), isPlaying(false), isPaused(false) {}

    void addTrack(const Track& track) {
        tracks.push_back(track);
    }

    void play(const std::string& name) {
        if (isPlaying) return;
        for (auto& track : tracks) {
            if (track.name == name) {
                currentTrack = &track;
                isPlaying = true;
                isPaused = false;
                std::cout << "Playing: " << track.name << "\nDate: " << std::asctime(&track.date)
                          << "Duration: " << track.duration << "s\n";
                return;
            }
        }
        std::cout << "Track not found.\n";
    }

    void pause() {
        if (isPlaying && !isPaused) {
            isPaused = true;
            std::cout << "Paused.\n";
        }
    }

    void next() {
        if (tracks.empty()) return;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, tracks.size()-1);
        currentTrack = &tracks[dist(gen)];
        isPlaying = true;
        isPaused = false;
        std::cout << "Playing next: " << currentTrack->name << "\n";
    }

    void stop() {
        if (isPlaying || isPaused) {
            isPlaying = false;
            isPaused = false;
            currentTrack = nullptr;
            std::cout << "Stopped.\n";
        }
    }
};

int main() {
    Player player;
    std::tm date = {};
    date.tm_year = 124;
    date.tm_mon = 5;
    date.tm_mday = 1;
    player.addTrack(Track("Track1", date, 300));
    player.addTrack(Track("Track2", date, 240));

    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        if (command == "play") {
            std::cout << "Enter track name: ";
            std::string name;
            std::getline(std::cin, name);
            player.play(name);
        } else if (command == "pause") {
            player.pause();
        } else if (command == "next") {
            player.next();
        } else if (command == "stop") {
            player.stop();
        } else if (command == "exit") {
            break;
        }
    }
}