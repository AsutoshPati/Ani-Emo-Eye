# An-Emo-Eye

The project is an innovative approach to integrating emotional intelligence into robotics. It features a dynamic robot eye animation displayed on a 0.96" OLED screen that changes based on the sentiment of text input provided by the user. The project is powered by the CAP10 Pratham, a made-in-India microcontroller board.

### Features
- **Real-Time Sentiment Analysis:** The system detects the sentiment of the user's text input.
- **Emotional Intelligence:** Enhances user interaction by allowing the robot to visually express emotions.
- **Compact Design:** Utilizes a 0.96" OLED screen for a minimalistic yet effective display.
- **Cost-Effective:** Built using the CAP10 Pratham board, making it an affordable solution for integrating emotional responses into robotics.

### Hardware Components
- **System/Edge Computing Device:** Any System capable of running sentiment analysis program.
- **CAP10 Pratham:** A programmable microcontroller board to control the OLED screen and handle the request from master system.
- **0.96" OLED Display:** A compact screen to display the animated robot eye.
- **Power Supply:** Ensure a stable power source for consistent operation.

### Software Requirements
**Python:** For sentiment analysis using LSTM (Long Short-Term Memory) models.
**Arduino IDE:** To program the CAP10 Pratham board and control the OLED display.

### Libraries:
- Please checkout **[requirements.txt](./requirements.txt)** for python libraries.
- **ESP32** board manager for Arduino IDE for programming CAP10 Pratham.
- **Adafruit_SSD1306** & **Adafruit_GFX** by Adafruit; for handling the OLED display & graphics functions.

### How It Works
- **Train Model (Optional):** Users can train the model using the dataset available in the [data](./data) directory or with their own data in the same format. Upon completion, they will receive the trained model for making predictions.
- **Sentiment Analysis:** The user provides a text input, then the sentiment of the text is analyzed using an LSTM model trained in the previous step.
- **Animation Update:** The CAP10 Pratham board receives the sentiment result by an API call and updates the OLED display with the corresponding eye animation (e.g., happy, sad, surprised).

### Installation
- **Software Setup**
    - Clone this repository:
        ```bash
        git clone https://github.com/AsutoshPati/An-Emo-Eye.git
        ```
    - Install the required Python packages:
        ```bash
        pip install -r requirements.txt
        ```
    - Upload the Arduino code available in [Display_Emotion](./Display_Emotion) directory to CAP10 Pratham board by selecting `ESP32 Dev Module` as board using the Arduino IDE.
- **Hardware Setup**
    - Connect the 0.96" OLED display to the CAP10 Pratham board. as mentioned in the [circuit diagram](./An-Emo-Eye%20Circuit%20Diagram.png)  
    ![Circuit Diagram](./An-Emo-Eye%20Circuit%20Diagram.png)
    - Ensure all components are securely connected and powered.
- **Usage**
    - (Optional) To Train the model run the training code [Sentiment Analysis.ipynb](./Sentiment%20Analysis.ipynb) in Jupyter Notebook.
    - If the Arduino code is successfully uploaded to CAP10 Pratham and the device is properly powered, a Wi-Fi Access Point with the SSID `CAP10 Eye` will become visible. To proceed, connect to this SSID from the master system (where the sentiment analysis script will be executed) using the password `12345678`.
    - Run the sentiment analysis [Prediction and Integration.ipynb](./Prediction%20and%20Integration.ipynb) script in the Jupyter Notebook.
    - Provide text input to the system and watch the OLED display as the robot eye changes based on the sentiment of the input.

### Applications
- **Interactive Robotics:** Enhance user interaction by allowing robots to express emotions visually.
- **Educational Projects:** Ideal for teaching concepts related to emotional intelligence in robotics.
- **Prototype Development:** Can be used in developing more complex emotionally aware robotic systems.

### Acknowledgments
Special thanks to my friend [Santosh](https://github.com/ask-santosh) for significant contributions to this project.

### License
This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

### Contributing
Don't forget to star the repository and connect with [me](https://www.instagram.com/mu_asutosh_pati/) if you find it helpful. Feel free to fork this repository and take your innovations to the next level.
