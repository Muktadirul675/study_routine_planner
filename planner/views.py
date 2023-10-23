from django.shortcuts import render
from . import models, serializers
from django.http import JsonResponse
import json

# Create your views here.

def home(request):
    subjects = models.Subject.objects.all()
    serializer = serializers.SubjectSerializer(subjects, many=True)
    cont = {'subjects':serializer.data,'json':json.dumps(serializer.data)}
    return render(request, "./planner/home.html",cont)

def makeRoutine(data,day):
    def findLowestIndex(array:list()):
        index = 0
        lowest = len(array[0])
        print(len(array))
        for a in range(len(array)):
            print(f'index {a} value {len(array[a])} lowest {lowest}')
            if len(array[a]) < lowest:
                index = a
                lowest = len(array[a])
        return index
    
    print(data)
    routine = []
    for i in range(day):
        routine.append([])
    totalSubjects = len(data)
    totalLectures = 0
    for i in data:
        totalLectures += i["lectures"]
    while True:
        oneDayLecture = []
        for sub in range(totalSubjects):
            subject = data[sub]
            name = subject["name"]
            lectures = subject['lectures']
            if lectures != 0:
                perDayLecture = lectures // day
                if perDayLecture == 0:
                    perDayLecture = 1
                for lec in range(perDayLecture):
                    routine[findLowestIndex(routine)].append(name)
                    data[sub]["lectures"] = data[sub]["lectures"] - 1
                    totalLectures -= 1
        if totalLectures == 0:
            break
    classesAdded = 0
    for i in routine:
        classesAdded += len(i)
    print(classesAdded)
    return routine

def api(request):
    # if request.is_ajax():
    if request.method == "POST":
        data = json.loads(request.POST["input"])
        days = int(request.POST["days"])
        subjects = []
        for i in data:
            dictionary = data[i]
            dictionary["lectures"] = int(dictionary["lectures"])
            subjects.append(dictionary)
        routine = makeRoutine(subjects,days)

    return JsonResponse(routine, safe=False)
