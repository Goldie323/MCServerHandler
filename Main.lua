scriptName = {}

function Main()
    print("Hello, World!")
end

scriptName.Main = Main

function scriptName:Run()
    if self.Main then
        self.Main()
    else
        print("Main function not defined.")
    end
end

return scriptName