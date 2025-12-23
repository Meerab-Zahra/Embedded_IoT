
At first, my laptop was acting as the publisher and my groupmate’s laptop was acting as the subscriber. MQTT Explorer was running on her laptop because the broker IP we used was 172.20.10.13. We were connected to the same network, and the topic was home/AI_Lab00/temp, so the data published from my side was received and shown on her MQTT Explorer.

After that, we reversed the roles. My laptop became the subscriber, and MQTT Explorer was running on my laptop because the broker IP was 172.20.10.2. In this case, my groupmate was the publisher and the topic used was home/AI_Lab01/temp. Since my laptop was acting as the broker and subscribed to this topic, the data was received and displayed on my MQTT Explorer.
