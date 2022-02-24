# Unreal Audio DSP Template (UE5)

## WARNING: BEWARE THAT THE METASOUND CODE IS BASED ON UE5 EARLY ACCESS AND THE API/FUNCTIONALITY WILL CHANGE ONCE UE5 IS FINALLY RELEASED. THIS PROJECT WILL BE UPDATED ACCORDINGLY WHEN THAT HAPPENS.

![](https://user-images.githubusercontent.com/7047334/152259689-cd7fd6d8-6b54-4dc9-b444-41ddd1f1fcfe.png)

A simple Unreal 5 plugin with demo content that shows how audio DSP processing can be done implementing a **Metasound Node**, **SourceEffect** and **SubmixEffect**.

A volume effect with its amplitude parameter is used to demonstrate how to do basic DSP processing.

The intention of this project is to use it as a start point to create more complex audio DSP effects.

The most relevant parts of the code are located in:
- *Plugins/AudioDSPTemplate/Source/AudioDSPTemplate/Private*
- *Plugins/AudioDSPTemplate/Source/AudioDSPTemplate/Public*

### Build steps:
- **Clone** repository
- Right click ***UEAudioDSPTemplate.uproject*** > *Generate Visual Studio projects files*
- Open ***UEAudioDSPTemplate.sln***
- **Build** Solution


### Testing the plugin:
- Open ***UEAudioDSPTemplate.uproject*** (or start it from Visual Studio)
- **DemoMap** will be automatically loaded
- **Metasound:**
    - Open **VolumeNode_Metasound asset**
    - Click ***Play*** button to start the Metasound
- **SourceEffect** and **SubmixEffect:**
    - Go to ***Blueprints*** > ***Open Level Blueprint***
    - You will see that there is Blueprint logic to trigger a sound at the Sphere location and a Timeline that will drive the *Amplitude* parameter of the SourceEffect
    - If you want to test the Submix effect simply connect the Update port from Timeline to the Set Settings node of the SubmixEffect
    - Click ***Play*** button to start the Level

<br/>

**Metasound:**
<br/>
![](https://user-images.githubusercontent.com/7047334/152261222-02493027-7379-49d8-96d1-0eeb658b72d0.gif)

**SourceEffect** and **SubmixEffect:**
<br/>
![](https://user-images.githubusercontent.com/7047334/152260190-42d02f7c-8b2f-4ff7-8cd3-1589361a621b.gif)
