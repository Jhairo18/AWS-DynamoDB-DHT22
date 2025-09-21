import json      # Librería estándar de Python para manejar datos en formato JSON
import boto3     # SDK de AWS para interactuar con los servicios, en este caso DynamoDB

# Función principal que ejecuta AWS Lambda
# 'event' contiene los datos de entrada que se reciben al invocar la función
# 'context' contiene información del entorno de ejecución (no se usa en este ejemplo)
def lambda_handler(event, context):
    # Crear un cliente de DynamoDB usando boto3
    client = boto3.client('dynamodb')
    
    # Insertar un nuevo ítem en la tabla 'esp32Datav2'
    response = client.put_item(
        TableName='esp32Datav2',  # Nombre de la tabla en DynamoDB
        Item={
            # Cada atributo debe definirse con su tipo: "S" (string), "N" (número), "B" (binario)
            "tiempo": {"S": event["tiempo"]},  # Se guarda como string
            "temperatura": {"N": str(event["temperatura"])},  # Se guarda como número (convertido a string obligatorio en DynamoDB)
            "humedad": {"N": str(event["humedad"])}           # También se guarda como número
        }
    )
    
    # Por ahora solo devuelve 0 (se podría devolver el response para confirmar la operación)
    return 0
