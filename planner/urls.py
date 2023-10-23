from django.urls import path,include
from . import views

app_name = "planner"

urlpatterns = [
    path('',views.home,name="home"),
    path('api/',views.api),
]