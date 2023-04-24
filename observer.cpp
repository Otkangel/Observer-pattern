#include <iostream>
#include <vector>

using namespace std;

class Observer {
public:
    virtual void update(float temp, 
                     float humidity, float pressure) = 0;
};

class DisplayElement {
public:
    virtual void display() = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherData : public Subject {
private:
    vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;
public:
    WeatherData() {
        temperature = 0.0f;
        humidity = 0.0f;
        pressure = 0.0f;
    }

    void registerObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        for (int i = 0; i < observers.size(); i++) {
            if (observers[i] == o) {
                observers.erase(observers.begin() + i);
                break;
            }
        }
    }

    void notifyObservers() {
        for (int i = 0; i < observers.size(); i++) {
            observers[i]->update(temperature, humidity, pressure);
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
    float temperature;
    float humidity;
    Subject* weatherData;
public:
    CurrentConditionsDisplay(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "Current conditions: " << temperature << " F degrees and " << humidity << "% humidity" << endl;
    }
};
class StatisticsDisplay : public Observer, public DisplayElement {
private:
    Subject* weatherData;
public:
    StatisticsDisplay(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        // Update statistics based on new measurements
    }

    void display() override {
        // Display statistics
    }
};
class ForecastDisplay : public Observer, public DisplayElement {
private:
    Subject* weatherData;
public:
    ForecastDisplay(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        // Update forecast based on new measurements
    }

    void display() override {
        // Display forecast
    }
};
int main() {
    WeatherData* weatherData = new WeatherData();
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
    StatisticsDisplay* statisticsDisplay = new StatisticsDisplay(weatherData);
    ForecastDisplay* forecastDisplay = new ForecastDisplay(weatherData);

    weatherData->setMeasurements(80, 65, 30.4f);
    weatherData->setMeasurements(82, 70, 29.2f);
    weatherData->setMeasurements(90, 53, 32.5f);

    delete currentDisplay;
    delete weatherData;
    delete statisticsDisplay;
    delete forecastDisplay;

    return 0;
}

