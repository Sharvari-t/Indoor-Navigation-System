import json
from os.path import join, dirname
from os import environ
from watson_developer_cloud import VisualRecognitionV3
visual_recognition = VisualRecognitionV3('2016-05-20', api_key="fbf4802cfa4ac9f3fd17c34fea19b964788cfdf4")

#print(json.dumps(visual_recognition.get_classifier('WetSegregation_1531006068'),indent=2))
print(json.dumps(visual_recognition.classify(images_url="http://simplecraftidea.com/wp-content/uploads/2015/05/342.jpg", classifier_ids="WetSegregation_1531006068"), indent=2))
