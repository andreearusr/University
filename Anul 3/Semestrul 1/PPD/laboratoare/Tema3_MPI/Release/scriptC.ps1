$noRuns = $args[0]

$average = 0

for($i = 0; $i -lt $noRuns; $i++){
    
    $startTime = (Get-Date)

    mpiexec -n 4 Tema3_MPI.exe

    $endTime = (Get-Date)
   
    $diff = $endTime - $startTime
    Write-Host $diff
    $average += $diff.ToString().SubString(9,3)
}

$media = $average/$noRuns
Write-Host "Timp executie mediu: " $media