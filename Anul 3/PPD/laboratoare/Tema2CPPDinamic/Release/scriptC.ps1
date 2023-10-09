
$param1 = $args[0] # Nume fisier exe
$param2 = $args[1] # No of threads
$param3 = $args[2]  # seq/par = type
$param4 = $args[3]  # No of runs

# Executare exe in cmd mode

$suma = 0

for ($i = 0; $i -lt $param4; $i++){
    $a = (cmd /c .\$param1 $param2 $param3 2`>`&1)
    Write-Host $a
    Write-Host $a[$a.length-1]
    $suma += $a[0]
}
$media = $suma / $i
#Write-Host $suma
Write-Host "Timp de executie mediu:" $media

# Creare fisier .csv
if (!(Test-Path outC.csv)){
    New-Item outC.csv -ItemType File
    #Scrie date in csv
    Set-Content outC.csv 'Tip Matrice,Tip alocare,Nr threads,Timp executie'
}

# Append
Add-Content outC.csv ",,$($args[1]),$($media)"