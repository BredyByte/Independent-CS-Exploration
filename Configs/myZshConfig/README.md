# 🌇 My Zsh Config

Welcome to my personalized Zsh configuration file! This README will guide you through the setup process, including creating the file if it doesn't exist and installing the essential plugins that I use in my Zsh terminal.

## 📖 Usage

1. **If you don't have a .zshrc file yet:**
- Create it by running the following command: `touch ~/.zshrc`. This will create a `.zshrc` file in your home directory.
- Copy and paste the contents of my file into yours.

2. **Install the necessary dependencies:**
- Run the following command to install Oh My Zsh:
     ```bash
     sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
     ```
     - This command downloads and installs Oh My Zsh, a powerful Zsh framework.
   
- Run the following command to install the `zsh-syntax-highlighting` plugin:
    ```bash
    git clone https://github.com/zsh-users/zsh-syntax-highlighting.git \
      ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
    ```
    - This plugin provides syntax highlighting.
   
- Run the following command to install the `zsh-autosuggestions` plugin:
    ```bash
    git clone https://github.com/zsh-users/zsh-autosuggestions.git \
      ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
    ```
    - This plugin enables auto-completion of your commands.
   
- To install the `autojump` plugin, execute the following command:
    - For Homebrew (macOS):
         ```bash
         brew update && brew install autojump
         ```
    
    - For apt (Debian/Ubuntu):
         ```bash
         sudo apt-get update && sudo apt-get install autojump
         ```
    After installing move manually the folder `autojump` from /.oh-my-zsh/plugins to /.oh-my-zsh/custom/plugins
    
    - Git clone installing without moving the folder:
         ```bash
         git clone git://github.com/wting/autojump.git \
           ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/autojump
         ```
3. **Reload your console, and everything should work!**
- To reload the console, execute
    ```bash
    source "path_to_.zshrc"/.zshrc  # (e.g., ~/.zshrc)
    ```

4. **Review the comments in the zshrc file:**
   - Customize the settings based on your preferences.
   - Feel free to remove or add configurations according to your needs.
   - If you encounter issues or have suggestions, don't hesitate to contribute or create an issue.

Happy coding with your newly customized environment! 🚀
