// vocab.h - kosakata NPC (Inggris = utama, Indonesia, Spanyol) + nama cowok/cewek. Boleh ditambah sendiri kapan saja.
// {n} di dalam kalimat = nama ped itu sendiri.
#pragma once
#include <cstddef>
#define POOL(NAME, ...) static const char* const NAME[] = { __VA_ARGS__ };

namespace VocabData {

// ===================== NAMA =====================
POOL(MALE_NAMES, "Aaron","Adam","Adrian","Alan","Albert","Alex","Andre","Andy","Anthony","Antonio","Arthur","Austin","Ben","Bill","Billy","Blake","Bobby","Brad","Brandon","Brian","Bruce","Caleb","Calvin","Carlos","Chad","Charles","Chris","Clarence","Cody","Colin","Corey","Craig","Curtis","Dale","Damon","Dan","Danny","Darius","Darnell","Dave","David","Dean","Dennis","Derek","Devin","Dominic","Doug","Dre","Dwayne","Earl","Eddie","Eli","Elijah","Eric","Ernest","Ethan","Felix","Frank","Gary","George","Glenn","Gordon","Greg","Hank","Harold","Hector","Henry","Howard","Ian","Isaac","Ivan","Jack","Jackson","Jacob","Jamal","James","Jason","Javier","Jay","Jeff","Jerome","Jesse","Jim","Joe","Joel","John","Jose","Josh","Juan","Justin","Keith","Kenny","Kevin","Kyle","Lamar","Larry","Leo","Leon","Lewis","Logan","Luis","Luke","Marcus","Mario","Mark","Martin","Marvin","Mateo","Matt","Max","Michael","Miguel","Mike","Nate","Neil","Nick","Noah","Omar","Oscar","Otis","Pablo","Paul","Pedro","Pete","Phil","Rafael","Ralph","Ramon","Randy","Ray","Reggie","Rick","Ricky","Rob","Roger","Roland","Ron","Ross","Roy","Russ","Ryan","Sam","Sean","Sergio","Seth","Shane","Stan","Steve","Terrell","Terry","Theo","Tim","Todd","Tom","Tony","Travis","Trevor","Tyler","Tyrone","Victor","Vince","Wade","Walter","Wayne","Will","Xavier","Zach")
POOL(FEMALE_NAMES, "Abby","Alice","Alicia","Alyssa","Amanda","Amber","Amy","Andrea","Angela","Angie","Anna","April","Ariana","Ashley","Audrey","Barbara","Beth","Bianca","Brenda","Brianna","Brittany","Candace","Carla","Carmen","Carol","Caroline","Cassandra","Charlene","Chelsea","Cheryl","Chloe","Christina","Cindy","Claire","Courtney","Crystal","Dana","Danielle","Dawn","Deborah","Denise","Diana","Donna","Dorothy","Elena","Elizabeth","Ella","Ellen","Emily","Emma","Erica","Erin","Eva","Evelyn","Faith","Fiona","Gabriela","Gina","Gloria","Grace","Hannah","Heather","Helen","Holly","Irene","Isabel","Jackie","Jada","Jamie","Jasmine","Jenna","Jennifer","Jenny","Jessica","Jill","Joan","Joanna","Josephine","Joy","Judy","Julia","Julie","Karen","Kate","Katie","Kayla","Keisha","Kelly","Kendra","Kim","Kristen","Laura","Lauren","Layla","Leah","Lena","Lisa","Lola","Lori","Lucia","Lupe","Lynn","Mara","Margaret","Maria","Marie","Marissa","Martha","Maya","Megan","Melanie","Melissa","Mia","Michelle","Mindy","Miranda","Monica","Monique","Nadia","Nancy","Naomi","Natalie","Natasha","Nicole","Nina","Olivia","Paige","Pamela","Patricia","Paula","Penny","Priscilla","Rachel","Rebecca","Renee","Rita","Roberta","Robin","Rosa","Rose","Ruby","Ruth","Sabrina","Sally","Samantha","Sandra","Sara","Sasha","Selena","Serena","Shannon","Sharon","Sheila","Shelly","Sierra","Sonia","Stacy","Stephanie","Sue","Summer","Susan","Tamara","Tanya","Tasha","Tessa","Tiffany","Tina","Tracy","Valerie","Vanessa","Vera","Veronica","Vicky","Violet","Wendy","Whitney","Yolanda","Yvonne","Zoe")
POOL(UNISEX_NAMES, "Alex","Jordan","Casey","Taylor","Morgan","Riley","Cameron","Drew","Quinn","Avery","Skyler","Jamie","Robin","Dana","Sam")

// ===================== INGGRIS: sapaan, kabar, nama =====================
POOL(EN_greet, "Hey, how's it going?","Yo, what's up?","Hey there, stranger.","Well hello!","Morning, man.","Evening.","Hi. You lost?","Hey. Need something?","What's good?","Howdy.","Look who it is.","Hey, you new around here?","Sup.","Hello, hello!","Oh, hi!","Heeey, what's happening?","Greetings, citizen.","Hey, nice to see a face that isn't scowling.","Yo yo yo!","Hi there. Lovely day for standing around.","Well, well, well.","Hey, you. Yeah, you.","Ahoy!","Hello there, friend.","Hey buddy, what's the word?","S'up, homie?","Hi! Don't mind me, just existing.","Hey, I was just thinking about nothing. Perfect timing.","Oh hey, a person. Hi, person.","Good day to you.","Hey, stranger danger. Kidding. Hi.","Yo, what brings you to this fine sidewalk?","Hello, and welcome to my personal space.","Hey! You look like you've got a story.","How do you do?","Hola, amigo!","Top of the morning to ya!","Hey, hey, hey!","Salutations!","Look at you, out and about.","Hi. I'd shake your hand but I just touched a gas pump.","Hey. Weird weather, huh?","Oh good, someone to talk to.","What's cooking, good looking?","Hi, I'm having a pretty normal day. You?")
POOL(EN_greet_angry, "What do you want?","Make it quick, pal.","Hmph. Something you need?","I'm not in the mood. What is it?","Yeah? What?","Talk fast, I'm busy.","Ugh. Hi. What?","You've got five seconds.","Not now, man.","What are you looking at?","Whatever you're selling, no.","Do I know you? Because I don't want to.","Oh great. Company.","Move it or say it.","Don't waste my time.")
POOL(EN_greet_scared, "H-hey... you're not gonna cause trouble, right?","Hi. I'm just passing through, man.","Oh! Hey. You scared me.","H-hello. Please keep your hands where I can see them.","Hi... is everything okay over there?","Uh, hey. I don't want any problems.","Hi. I was just about to leave, honest.","Oh no, a stranger. Hi.","Hello? Are you... friendly?","Hey. Do you hear that noise too?")
POOL(EN_greet_happy, "Hey there! Beautiful day, huh?","Yo! Good to see a friendly face!","Hi! Anything I can help you with?","Heyyy! You've made my day better already!","Well hello, sunshine!","Hi hi hi! How are you?!","Oh wow, hey! Great to see you!","Hey, friend! Wanna hear something awesome?","Hello! Life is good, isn't it?","Yooo! You look like you're having a great day too!","Hey! Smells like a good day out here.","What's up, champ?")
POOL(EN_howare_angry, "Terrible. Today's been nothing but headaches.","Don't ask. I'm in a rotten mood.","Pissed off, if you must know.","Worse now that you asked.","Like garbage. Next question.","Don't push it, pal.","Absolutely lovely. Can't you tell? Ugh.","Bad. Everything's bad.","Annoyed. Mostly at everything.","How do I look? Mad. That's how.")
POOL(EN_howare_scared, "A little on edge, honestly. This place isn't always safe.","I'm fine... just keeping my eyes open.","Nervous, man. Real nervous.","I keep hearing weird noises. You?","Okay, I guess. Please don't make any sudden moves.","Jumpy. Very jumpy.","I'd be better if I was home.","Shaky. Like three coffees too many.","Okay. I think. Maybe. Can I go now?","Fine, fine, totally fine. Why are you looking at me like that?")
POOL(EN_howare_happy, "Pretty damn good, man! Sun's out, nobody's bothering me.","Can't complain! How about you?","Living the dream, buddy.","Fantastic! I found a dollar earlier.","Great! I'm in an amazing mood today.","On top of the world!","Better than yesterday, worse than tomorrow.","Couldn't be better. Seriously.","Wonderful! Even the pigeons seem friendly.","Happy as a clam. Do clams know they're happy?","Awesome, thanks for asking! Most people don't.","Fantastic. Today I'm unstoppable.")
POOL(EN_howare, "Just getting by, you know how it is.","Same old, same old. You?","Not bad, not great.","Surviving. Mostly.","Meh. It's a Tuesday kind of day.","Alright. Could be better, could be worse.","I'm hanging in there.","Eh, can't complain. Well, I can, but nobody listens.","Pretty chill. You?","Doing okay. Tired, but okay.","I've had worse days. I've had better ones too.","Honestly? Confused, but in a good way.","Fine. My feet hurt.","Just vibing on the sidewalk.","Eh. Life's a rollercoaster and I forgot my ticket.","Good enough, I suppose.","Ask me again after coffee.","Functional. That's the word. Functional.","Hanging in there like a cat on a curtain.","Nothing to report, officer. I mean, friend.")
POOL(EN_name, "I'm {n}. And you?","Name's {n}. Been hanging around this block for years.","Call me {n}.","{n}. Nice to meet you, I guess.","It's {n}. Don't wear it out.","{n}, at your service.","They call me {n}. Mostly my mom.","I'm {n}. Not famous. Yet.","Name's {n}. Why, you writing a book?","{n}. Like it? I picked it myself. Okay, my parents did.","The name's {n}. {n} with the sidewalk and everything.","I go by {n}. Sometimes 'hey you' too.","{n}. Remember it, you'll need it for my autograph.","Why, I'm {n}! And who might you be?","Folks round here call me {n}.","{n}. Two syllables of pure charm.","It's {n}. Spelled exactly how it sounds.","I'm {n}. I'd say pleased to meet you, but let's see how this goes.","{n}. Don't ask about my middle name.","Me? {n}. I'm nobody important.")

// ===================== INGGRIS: terima kasih, pamit, maaf, ya, tidak =====================
POOL(EN_thanks, "No problem, buddy!","Anytime, man. Take it easy.","Heh, you're welcome. Stay safe out here.","Don't mention it.","Sure thing!","Hey, that's what neighbors are for.","My pleasure. Honest.","No sweat.","You got it, friend.","Aw, shucks. You're welcome.","Think nothing of it.","Anytime. And I mean anytime. Even 3 AM.","Yeah, yeah, don't get mushy on me.","Glad I could help. I think.","You're welcome! Now I feel important.","It was nothing. Okay, it was a little something.","Easy. Just doing my part for humanity.","No thanks needed, but I'll take them anyway.","De nada, amigo!","Stop it, you'll make me blush.","You're too kind. Please keep going.","Cool. We're even. Wait, did I owe you something?","Ha, nobody ever says thanks. You're a rare one.","Of course! That's the spirit.","Well aren't you polite!")
POOL(EN_bye, "Alright, take care out there.","See you around, man.","Take it easy.","Later, alligator.","Don't be a stranger, alright?","Catch you on the flip side.","Bye now!","Stay safe, friend.","Peace out.","So long, partner.","Adios!","Don't do anything I wouldn't do. That leaves a lot of room.","See ya. Wouldn't wanna be ya. Kidding.","Alright, I'm gonna go stare at a wall somewhere.","Goodbye, and may your shoes never get wet.","Til next time!","Hasta la vista.","Go on, get out of here.","Smell you later.","Take care, and watch out for pigeons.","Bye! I'll miss you for roughly four minutes.","Farewell, traveler.","Off you go then. Don't talk to strangers. Oh wait.","Cheers, mate!","Be good. Or be careful. Or both.","See you when I see you.","Later, friend. The block won't be the same.","Walk safe!","Keep your head up.","Ciao!")
POOL(EN_sorry, "It's fine, forget it.","Don't worry about it.","Apology accepted. This time.","Eh, it happens.","No harm done, I guess.","Alright, we're cool.","Thanks for saying that. Most people don't.","Hey, we all mess up. Water under the bridge.","Okay, okay, I'm over it.","That means a lot, honestly.","Don't sweat it, man.","Sure. Just don't do it again. Or do, I'm not your mom.","Apology received, filed, and laminated.","I forgive you. Barely. Kidding.","It's all good.")
POOL(EN_yes, "Heh, glad we agree.","Right? That's what I'm saying.","Exactly. Finally, someone gets it.","See, you're smart.","Yep, that's how it goes.","Damn right.","Sounds good to me.","Alright then.","Good, good.","Yeah, that's the spirit.","Mm-hmm. I thought so.","Great, one point for us.","Hey, we're on the same page.","I knew you were sensible.","Look at us, agreeing. Revolutionary.")
POOL(EN_no, "Aw, c'mon, why not?","Fine, be that way.","Okay, okay, no need to be dramatic.","Hmm, your loss.","Suit yourself.","Wow, such enthusiasm.","Alright, I'll cry about it later.","No? Huh. Interesting.","Bold of you to say no to me.","Whatever you say, boss.","Okay. I wasn't invested anyway.","Noted. Filed under 'rude'.","Alright then, be like that.","Your call, buddy.","Fair enough. I respect the confidence.")

// ===================== INGGRIS: uang, arah, cinta, pujian =====================
POOL(EN_money, "Money, huh? Now you're speaking my language.","I'm tight on cash, man. Sorry.","Nope, nothing to spare right now.","Wish I could help, I'm flat broke.","Cash is king, but my pockets are peasants.","I've got three dollars and a gum wrapper. Take it.","Everybody wants money. Nobody wants to earn it.","Ask someone with a nicer car.","I spent my last dollar on a hot dog. No regrets.","If I had money, would I be standing here?","I don't lend. Lessons learned.","I know a guy who knows a guy with money. Doesn't help you though.","You sound like my landlord.","Money's overrated. Said every broke person ever.","I'd give you some, but I'm saving for a sandwich.","Do I look like a bank to you?","My wallet's been on a diet for months.","The only thing I'm rich in is opinions.","Cash? I only carry vibes.","Sorry, my money's tied up in snacks.","Get a job, buddy. Kidding. Maybe.","I'm allergic to lending money. Hives and everything.","What do you need it for? Tell me it's pizza.","Talk to me when you've got a business plan.","I've got a coupon for two free fries. Want it?","If you find a way to print money, call me.","Money talks. Mine says goodbye.","I'm saving up for a boat. So far I've got a paddle.","I'd love to help, but I owe three people already.","Not today, friend. Not tomorrow either.")
POOL(EN_directions, "Sorry, I'm not from around here.","Just keep going straight, you'll find it. Probably.","I only know this block, man.","Left, then right, then... honestly I forgot.","Follow the smell of tacos, you can't miss it.","Ask someone else, I'm not a tour guide.","Down that way, near the thing with the other thing.","I'd say turn left but I'm always wrong.","It's over there. Past the place. By the stuff.","Check your phone, genius. Kidding. I don't know either.","Head that way until you see a pigeon. Then turn.","I got lost on my way to my own house yesterday.","There's a shortcut, but it involves a fence and regret.","Honestly, just follow the sirens.","It's like two blocks away. Or ten. Distance is weird.","Walk until you feel lost, then walk a bit more.","I think it's near the gas station. Or the other gas station.","Go straight, make a left at the tree, and pray.","Try the main road. Everything's on the main road. Probably.","Sorry, I don't speak 'directions'.","It's that way. Trust me. Don't trust me.","If you find it, tell me where it is.","I've only ever walked in circles around here.","Keep the sun on your left. Or right. Depends on the time.","I'd draw you a map but I forgot a pen.")
POOL(EN_love, "Ha! Smooth. Real smooth.","You flirting with me? Bold move.","Careful, you'll make me blush.","Aw, you're sweet.","Wow, straight to the point, huh?","I'm flattered. Confused, but flattered.","Buy me dinner first.","Slow down, we just met.","Oh stop it, you!","That line works on exactly zero people.","My heart is taken. By tacos.","I'm taken. By my own schedule.","You're cute when you try.","Is that a pickup line or a cry for help?","I'd say yes, but my cat disapproves.","Wow. Okay. Hi. Did not expect that.","My mother always said beware of smooth talkers.","Interesting approach. Ten out of ten for courage.","Let's get to know each other first. Like, my name's {n}.","I'm blushing. Look away.","Save the compliments, I have low self esteem and high bills.","Take a number, please. You're 47.","Hmm, tempting. But no.","You say that to everyone, don't you?","That's the nicest thing anyone's said to me all week.")
POOL(EN_compliment, "Thanks, I try.","Heh, I'll take it.","You're not so bad yourself.","Appreciate that, man.","Aw, now I'm blushing.","You've got good taste.","Finally, someone with eyes.","Flattery will get you everywhere.","I know, right? I'm a gem.","That's the nicest thing I've heard all day.","Careful, my ego is already enormous.","Stop, I'm gonna cry. Or float.","Wow. Okay. Thanks.","You should tell my boss that.","I'd like to thank my parents, my agent, and my shoes.","Right back at you, friend.","Hey, you're making me feel special.","You really mean that? Aw.","I'll be thinking about that for the rest of the week.","My mirror says the same thing.")

// ===================== INGGRIS: hinaan & ancaman (reaksi) =====================
POOL(EN_insult_nervous, "Wow... that was rude. What did I do?","Okay, okay, no need to yell.","I'm just gonna walk away now.","That hurt, man. That actually hurt.","Why are you being mean to me?","I didn't do anything to you!","Please don't be like that...","I'm gonna pretend I didn't hear that.","Okay. Okay. I'm leaving.","My feelings! Are a thing!")
POOL(EN_insult_tough, "Say that again, I dare you!","Big mouth for someone who doesn't know me.","Careful, pal. I'm not in the mood.","You wanna run that by me again?","Funny. Say it to my face. Oh wait, you are.","You've got some nerve.","Keep talking. See where it gets you.","That's the dumbest thing I've heard today. And I met a guy with a ferret on his head.","I've eaten tougher guys than you for breakfast.","Watch it. Seriously.","Your mama teach you that? Mine taught me to fight.","Bold words for someone so short on friends.","Ooh, scary. Not.","Careful, I bite.","You're lucky I'm in a good mood. I'm not.")
POOL(EN_insult_neutral, "Damn, that was uncalled for.","Chill out, man. I didn't do anything to you.","Rough day, huh?","Wow. Rude. Just rude.","Okay, ouch.","Did you wake up on the wrong side of the sidewalk?","You kiss your mother with that mouth?","Alright, that's enough of that.","Somebody needs a nap.","Take a breath, buddy.","What did I ever do to you?","Impressive. A whole insult with zero creativity.","I'm choosing to ignore that.","Hey, no need to bring me into your bad day.","Wow, harsh. Let me write that down so I can forget it.")
POOL(EN_threat_scared, "Whoa, easy man! I don't want any trouble!","P-please don't hurt me, I'll just go!","Okay okay, I'm leaving, just stay calm!","Don't! I've got a family! And a goldfish!","I'm nobody! Just let me go!","H-hey, let's talk about this like adults!","I'll give you anything! Well, not much. I have two dollars.","I didn't see anything, I swear!","Please! I'm too pretty to die!","Okay, I'm backing away slowly!")
POOL(EN_threat_tough, "You really wanna do this? Bad idea, pal.","I've dealt with tougher guys than you.","Try me. See what happens.","You couldn't hurt a sandwich.","Go ahead. I haven't had a good fight all week.","Big talk. Let's see the walk.","You and what army?","Do it. I dare you.","Keep your hands where I can see 'em.","You picked the wrong person, buddy.","I'm not scared. I'm mildly annoyed.","Oh, you're serious? That's adorable.")
POOL(EN_threat_neutral, "Hey, back off. I'll call the cops!","Watch your mouth, buddy.","Not cool, man. Not cool at all.","Whoa, whoa, let's all calm down.","That's not funny.","You need to chill. Like, right now.","Somebody call someone!","I don't want trouble, but I'll make some if I have to.","Back up. I'm serious.","You're acting crazy right now.","Easy there, tough guy.","I'm walking away. This conversation is over.")

// ===================== INGGRIS: topik obrolan =====================
POOL(EN_joke, "Why don't skeletons fight each other? They don't have the guts.","I told my wife she was drawing her eyebrows too high. She looked surprised.","I'm reading a book about anti-gravity. It's impossible to put down.","Why did the scarecrow win an award? He was outstanding in his field.","I used to hate facial hair, but then it grew on me.","What do you call fake spaghetti? An impasta.","I only know 25 letters of the alphabet. I don't know y.","Why did the bicycle fall over? It was two-tired.","Why can't you trust atoms? They make up everything.","I'd tell you a construction joke, but I'm still working on it.","What do you call a bear with no teeth? A gummy bear.","I'm on a seafood diet. I see food and I eat it.","Parallel lines have so much in common. It's a shame they'll never meet.","Why did the tomato blush? It saw the salad dressing.","My dog used to chase people on a bike. I had to take it away from him.","What's brown and sticky? A stick.","Knock knock. Who's there? Not me, I'm just walking.","Two guys walk into a bar. The third one ducks.","What did the ocean say to the beach? Nothing, it just waved.","I tried to catch fog yesterday. Mist.","Want to hear a joke about paper? Never mind, it's tearable.","I got a job at a bakery because I kneaded dough.","What do you call a sleeping bull? A bulldozer.","Why do bees have sticky hair? Honeycombs.","I once met a guy who said he could breathe underwater. Fishy.","How do you organize a space party? You planet.","I wanted to be a doctor, but I didn't have the patients.","What's a pirate's favorite letter? Arr, you'd think it's R, but it's the C.","I'm afraid for the calendar. Its days are numbered.","Why did the coffee file a police report? It got mugged.")
POOL(EN_weather, "Weather's been weird lately, huh?","Sun's out. Can't complain.","I think it's gonna rain. My knee says so.","Too hot. Way too hot. Why is it so hot?","I love the rain. Makes the city feel cleaner.","It's always sunny in Los Santos. Except when it's not.","Forecast says clear. Forecast lies.","Smog today looks extra purple. That's normal, right?","Nice breeze. Smells like fast food and ambition.","Hot enough to fry an egg on the hood of that car.","I checked the weather and it said 'weather'. Helpful.","Cold fronts, warm fronts, I just want a dry front.","My hair knows when it's about to rain. Frizz alert.","Perfect beach weather. Not that I've ever been.","If it rains, I'm blaming you.","Storm's coming. Can't you feel it? Or is that my stomach?","Clouds look like a duck today. Look. A duck.","Sunburn season. Bring a hat.","Gray skies. Perfect mood weather.","The sky looks like soup today.")
POOL(EN_food, "I could really go for a burger right now.","Pizza is the answer. The question doesn't matter.","Tacos. Always tacos. Never a bad time for tacos.","I'm starving. Seriously. I'd eat a shoe.","Coffee, man. Without it I'm just a grumpy statue.","Hot dog from a gas station? Gourmet.","My diet is 80% fast food and 20% regret.","Chicken is the greatest food ever invented. Fight me.","Best meal I ever had was at a drive-through at 2 AM.","Do you like pineapple on pizza? Choose wisely.","I put hot sauce on everything. Even cereal. Don't judge.","Ice cream for breakfast is a lifestyle.","Never trust a person who doesn't like fries.","I could eat a whole pizza by myself. And have.","Beer? Cold beer on a hot day? Heaven.","I make a mean sandwich. Ask no one.","Donuts. That's a food group, right?","Sushi's overrated. Give me chili cheese fries.","I cook better than I fight. Barely.","Lunch? Is it lunch time? It should be lunch time.","I like my steak like my coffee: loud and strong.","I just ate and I'm already hungry. Science is broken.","Free samples are my love language.","Whoever invented bacon deserves a statue.","If it's fried, I'm buying.")
POOL(EN_music, "Rap, rock, country, I'm into it all. Except polka.","Turn on the radio, man, always some good tunes.","I used to be in a band. We were called The Sidewalk Cracks.","Nothing beats classic hip hop.","I sing in the shower. Neighbors complain.","Got a favorite song? Mine's whatever's playing right now.","Oldies. Pure gold. They don't make 'em like that anymore.","My dream is to be a rock star. My reality is parking tickets.","Bass is the heartbeat of the city.","I can't dance, but I try. And fail. Loudly.","Music makes everything better. Even laundry.","Ever tried karaoke? I broke a window once.","Country music? Cry in your beer and be happy about it.","Good beat, good mood, good day.","I hum when I'm nervous. La la la.","My neighbor plays the trumpet at midnight. Why?","Funk, soul, and a little bit of chaos.","Every song is about love or cars. Or both.","If I could play one instrument, it'd be the triangle.","Turn it up, man. Turn it all the way up.")
POOL(EN_cars, "That's a nice ride. Mine's more of a rolling lawn chair.","I'm a Sentinel guy. Clean, fast, reliable.","Gas prices, man. It's highway robbery.","I once drove a car backwards for three miles. Long story.","Lowriders are art on wheels.","I know a guy who can fix anything with duct tape.","My car's got character. Mostly rust.","Never trust a car that makes a happy noise when it's broken.","Speed is a state of mind. And a ticket.","Bikes are better. Less traffic, more danger.","Engine's fine. It's the driver that's the problem.","My dream car is a Infernus. My actual car is a shopping cart.","Honk if you love tacos.","Whoever invented traffic should be gently thrown into traffic.","I love the smell of fresh tires.","Do you race? I race. Mostly to the bathroom.","Turbo, nitro, cup holders. The holy trinity.","My car broke down so I'm walking. Like a primitive man.","Parallel parking is a personality test.","I've never seen a clean taxi in my life.")
POOL(EN_police, "Cops? Don't get me started.","Best to keep your head down around the police.","I got a ticket for being 'too relaxed'. Is that a thing?","Donuts and doughnuts. That's all they care about.","I've never been arrested. Mostly.","If you see the cops, act natural. Or run. Your call.","Prison food can't be worse than what I make.","The police are everywhere. And nowhere when you need them.","I respect the law. From a distance.","A cop gave me a warning once. For jaywalking. At 3 AM. In an empty street.","Sirens give me anxiety. And rhythm.","Never talk to the police without a sandwich.","I saw a cop dance once. I think I imagined it.","Trouble finds me. I don't look for it.","Keep it legal, friend. Mostly.","Sheriff's got a mustache. That's all I know.","Cops are like pigeons. They're everywhere and they stare.","I'm just a regular citizen. Super regular.","Law and order, baby. Look it up.","Honestly, I'm more scared of the paperwork.")
POOL(EN_gang, "Gangs? I mind my own business. Mostly.","Colors matter around here. Watch what you wear.","This used to be a quiet neighborhood. Used to.","I know people who know people. That's all I'll say.","Turf wars are exhausting. And loud.","Stay out of other people's territory, friend.","My cousin's in a crew. He wears nice shirts.","Gangs, drugs, rain. That's Los Santos.","I don't wear red. Or blue. Or green. Beige is safe.","Everybody's got a crew. Mine's two pigeons and a squirrel.","Respect gets you farther than a gun.","It's not about colors, it's about family. Or so they say.","I don't do the gang thing. Too much matching.","You hear gunshots at night? Ignore them. That's the rule.","Loyalty over everything, man.","Hood's got its rules. Learn them.","Some folks join up for the jackets.","Be careful where you walk at night.","I'm neutral. Like Switzerland. With worse food.","Homies are good, but peace is better.")
POOL(EN_work, "Work? Don't remind me.","I've got three jobs and zero free time.","My boss is a nightmare. A tiny, loud nightmare.","I'm between jobs. For six years.","Retail, man. It'll make you hate people.","I'd love to quit, but my bills would miss me.","I deliver pizzas. Very rewarding when they're hot.","Work hard, play harder, nap hardest.","Do you know how many emails I ignored today? Eighty.","My job's okay. The coffee's the star.","I want to start my own business. Selling air.","Success is just failure with better lighting.","I sell insurance. Please don't walk away.","My dream job is professional napper.","I work in the shadows. And on weekends.","Every day is Monday when you hate Mondays.","The grind never stops. It just makes weird noises.","I got fired for being too honest. Allegedly.","I work for tips. Mostly I tip over.","Honest work. Dishonest pay.")
POOL(EN_family, "Family's complicated. Mine especially.","My mom would kill me if she saw me out here.","My brother owes me money. And a sandwich.","I've got two sisters. They run everything.","My dad always said: work hard, don't talk to strangers. I'm failing both.","Family barbecues are the best. And the worst.","I call my mother every Sunday. Sometimes.","My kids drive me nuts. I love them though.","My cousin thinks he's famous. He's not.","You got siblings? They're a blessing and a curse.","My uncle tells the same story every holiday.","Family comes first. Then snacks.","I'd do anything for my family. Except laundry.","My grandma could beat anyone in a fight. Respect.","My folks are in Vinewood. Not famous. Just living there.","Aunt Linda knows everything about everyone.","My parents think I'm a doctor. I'm not.","Brothers and sisters, man. Can't live with 'em.","Holiday dinners are a war zone with gravy.","Love my family. From afar. With distance.")
POOL(EN_age, "Old enough to know better. Young enough not to care.","I'm 29. Or 39. I lose track.","Age is just a number. A big, annoying number.","I feel 20 in my head and 80 in my knees.","Never ask a person their age. Or their weight. Or their ex.","Somewhere between 'young' and 'tired'.","Thirty-ish. Maybe forty-ish. Ish.","I'm as old as my tongue and a little older than my teeth.","I stopped counting after 25. Technically I'm still 25.","Why, how old do I look? Be honest. Actually don't.","Old enough to remember when gas was cheap.","I'm a classic. Like vintage wine. Or vinegar.","Too old for this, too young to stop.","Age? Let's say I'm a fine vintage.","I was born yesterday. Obviously not, but it feels like it.")
POOL(EN_from, "Born and raised right here in Los Santos.","I'm from out of state. Miss it every day.","From the East Coast. Don't ask which part.","I moved here for the weather. Smog was a surprise.","I'm from a small town you've never heard of.","From Texas originally. We do everything bigger. Including mistakes.","Grew up in Ganton. Still here. Still fighting.","Came here for a dream. Found traffic.","From San Fierro. The fog follows me.","Born in a hospital like everyone else. Kidding. Wolf pack.","From Vinewood. Not the cool part.","I've been everywhere. Mostly bus stops.","Grew up on a farm. Ran away to find air conditioning.","I'm a local. Ask anyone. They'll lie, but still.","Moved around a lot. Home is wherever there's Wi-Fi.")
POOL(EN_time, "No watch, man. Ask the sun.","Time to get a watch, it looks like.","It's probably time for lunch.","Time flies. Usually when I'm not looking.","I have no idea. Time is a construct.","Late. We're always late.","Check your phone, genius.","It's either early or late. Not sure which.","Late enough to be tired, early enough to be hopeful.","About quarter to whenever.","Time's relative. Mine's usually wrong.","Don't ask me. I live in the moment. Which is currently now.","I'd check but my watch is broken. It's right twice a day though.","It's always happy hour somewhere.","Ask me again in an hour. It'll be later.")
POOL(EN_help, "What do you need? Make it quick.","Help? I'm not great at helping. But I'll try.","Call 911, buddy. I'm not a doctor.","I'd help but I'm kinda busy being useless.","Sure, what's up? Is it dangerous? Don't say dangerous.","Of course I'll help. Eventually.","Don't look at me, I'm just a bystander.","Okay, okay, I'm here. What's wrong?","Calm down and tell me everything.","I can offer moral support. And half a sandwich.","If it's heavy, I can't lift it. If it's light, sure.","I'm not a hero. But I'll hold your coat.","Quick, someone call someone!","Let me help. I read about it once.","What happened? Are you bleeding? Please say no.")
POOL(EN_sleep, "Sleep? What's that? I forgot.","I'm so tired I could nap standing up.","Coffee, then sleep. Or the other way around.","I haven't slept in two days. Everything looks purple.","Beds are the greatest invention ever.","Insomnia's a real jerk.","I dream about tacos. Every night.","Nap time is my favorite time.","If you can't sleep, count sheep. Or cars.","I sleep like a log. A really loud log.","My neighbor's dog never lets me sleep.","Sleep is for the weak. And the rested.","I slept on a park bench last night. Comfy? No.","Dreams are free movies. Mine are low-budget.","Eight hours? Sounds like a fantasy.")
POOL(EN_games, "Video games? Love 'em. I'm basically a pro.","I'm stuck on level three. Been stuck for a year.","Do you play? What's your favorite?","Games make time disappear. Mostly my time.","I used to play all night. Now I just nap.","I'm a casual gamer. Casual, but angry.","I always play the bad guy. It's just more fun.","Consoles are expensive. Controllers fly.","Never trust someone who only plays tutorials.","I'm still undefeated in rock paper scissors. Against myself.","There's a game where you steal cars. Sounds fun, doesn't it?","I once threw a controller through a window. Worth it.","Multiplayer's chaos. Single player's therapy.","The best game is life. The worst graphics though.","Do you cheat in games? I only cheat in checkers.")
POOL(EN_question, "Good question. Never thought about it.","Hard to say. What do you think?","Beats me, man.","Why do you ask?","That's above my pay grade.","Honestly? I have no idea.","Hmm. Maybe. Maybe not.","Ask me again later, my brain's buffering.","I'd say yes. But I'd also say no. Depends.","The real question is: who cares?","That's the million dollar question.","I could answer that, but I'd have to charge you.","Why would you ask me? Do I look smart?","Funny you should ask. I was just wondering the same.","I plead the fifth.","Deep. Too deep for noon.","It depends. On what? On everything.","Let me consult my imaginary friend. He says no.","I'll think about it and never tell you.","My therapist and I are still working on that.","What kind of question is that?","Everything is possible. Nothing is certain. Mostly.","That's a trick question, isn't it?","Do I look like Google?","Absolutely. Or not.","You ask a lot of questions for a stranger.","Fascinating. Next question.","If I knew, I'd tell you. Maybe.","That's classified. By me.","Eh. Probably.","I don't know, but I have feelings about it.","Short answer: yes. Long answer: it's complicated.","Why are you asking me this on a Tuesday?","Good one. I'll write it down and forget it.","The answer is 42. Always.")

// ===================== INGGRIS: balasan umum menurut mood =====================
POOL(EN_default_angry, "I'm not in the mood. Move along.","Whatever, pal.","Leave me alone.","Do I look like I care?","Talk to the hand.","Save it.","Not interested.","You're getting on my nerves.","Hmph.","Just go away.","Ugh. People.","That's your problem, not mine.","Keep walking.","Don't push your luck.","Don't you have somewhere to be?","I said what I said.","Great. Another genius.","Annoying. Truly.","One more word and I'm leaving.","Can you not?")
POOL(EN_default_scared, "Please don't get any closer...","You're making me uncomfortable.","I should really get going.","I don't know anything, I swear.","Are we alone here? I hope not.","I've got a bad feeling about this.","Maybe we should talk somewhere with more witnesses.","I think someone's following me.","Please don't hurt me. I'm not even tasty.","Okay. Okay. Okay. I'm fine.","My heart's racing, man.","Is that a gun? Please say no.","Let's just keep this friendly, yeah?","I'm gonna go now. Slowly. Don't follow.","Don't look behind you. Seriously.","I knew I should've stayed home.","This neighborhood gives me the creeps.","My palms are sweating.","I'm fine. I'm absolutely fine. Look how fine I am.","Please. Just be cool.")
POOL(EN_default_happy, "Ha! You're alright, you know that?","Life's good, man.","I like talking to you, honestly.","This is the best day ever!","You've got a good vibe.","I love this city!","Hahaha, you're hilarious.","Let's celebrate something! Anything!","Hey, I feel like singing!","Wow, you're fun.","You know what? Everything's gonna be fine.","What a day to be alive!","You should hang out with me more often.","We should start a band.","I'm in such a good mood, I might hug a stranger.","Look at us, having fun on a Tuesday.","Everything's coming up roses!","Honestly? Best conversation I've had all week.","Sometimes life just works out.","Man, I could talk to you all day.")
POOL(EN_default, "Hmm, I see.","Okay... and then?","Interesting.","I'm listening, go on.","That's how it goes around here.","Right, right.","Mm-hmm.","Sure, sure.","I can respect that.","Is that so?","Uh-huh. Tell me more.","Wow. Okay.","That's wild, man.","I mean, yeah. Fair.","I wouldn't know about that.","If you say so.","That's one way to look at it.","Huh. I never thought of it like that.","Alright, alright.","You don't say.","Makes sense. Sort of.","Cool, cool, cool.","Whoa. Deep.","And yet here we are.","Tell it to the pigeons.","Honestly? I'm just here for the sidewalk.","That's... a statement.","Okay, but why?","Funny, I was just thinking the same. Not really.","Life's a mystery. And a sandwich.")

// ===================== INGGRIS: gumaman acak / absurd / spontan =====================
POOL(EN_random, "I swear that cloud is following me.","Do you ever just stare at a wall and wonder if the wall is staring back?","Pigeons are government drones. I've said too much.","I wonder what ducks think about us.","My left sock keeps disappearing. It's a conspiracy.","Never trust a man who owns more than two hats.","I saw a squirrel carrying a slice of pizza. Respect.","I've been meaning to learn the accordion. For forty years.","Fun fact: sidewalks are just flat roads for people.","Somebody once told me tacos are a state of mind.","Why is it called a building if it's already built?","If I were a bird, I'd be a bad bird. Terrible at flying.","I keep misplacing my keys. Even when they're in my hand.","Is it normal to talk to yourself? Asking for me.","I think the moon owes me money.","Why do they call it rush hour when nothing moves?","I once won a hot dog eating contest. Lost the friendship.","My plants are judging me.","The sidewalk's warm. Like a giant, boring blanket.","I've named every pigeon on this street. That one's Gary.","Sometimes I walk backwards just to confuse people.","Humans are weird. I'm a human.","I bet I could fit a whole burrito in my mouth.","I think that dog just smiled at me.","One day I'll be famous. One day. Probably after lunch.","Is it just me, or does that building look sad?","My cat thinks she's a landlord.","What if the sun is just a giant lamp? Discuss.","I like looking at trash cans. They've seen things.","Sometimes I forget why I walked into a room. Outdoors too.","Somebody should invent shoes that tie themselves. Oh wait.","Why does gum lose flavor so fast? Corporate greed.","I think I left my oven on. In 2009.","One time, I got stuck in a revolving door for an hour.","I like to wave at strangers. Most wave back. Some call the cops.","Why is it called 'rush hour' when it's two hours?","I feel like I'm in a movie. A bad one.","I don't trust escalators. They're stairs with commitment issues.","If I were a vegetable, I'd be a potato. Reliable, but dull.","That mailbox gives me the stink eye.","I'm pretty sure my neighbor is a robot.","Some days, I feel like the main character. Today I'm an extra.","You ever hear a song and get emotional about a sandwich?","I once ate a whole watermelon. Alone. In a car.","I count the cracks on the sidewalk. Thirty-seven so far.","Why do I always get the shopping cart with the broken wheel?","I only floss when I'm lying to someone.","My life is a sitcom with a really low budget.","I'm 70% coffee, 20% sarcasm, 10% sidewalk.","The nicest people always have the loudest dogs.","I'd rather be in a hammock. Any hammock. Even a sad one.","People say money can't buy happiness. I say have they tried tacos?","I've never trusted a seagull. Especially the ones who smile.","I read the entire phone book once. Great plot, too many characters.","Is a hot dog a sandwich? Don't answer that.","My GPS keeps calling me 'recalculating'. Rude.","What do ghosts eat? Boo-ritos.","I got lost in my own neighborhood. Twice.","You ever feel like the universe is just buffering?","I still sleep with a nightlight. It's called a phone.","I carry an umbrella everywhere. It's never rained when I have it.","One time a pigeon stole my fries and I respected it.","I think shadows are just the sun's way of saying 'hi'.","What if we're all NPCs? Anyway, nice day.","The fire hydrant winked at me. Or I need glasses.","Sometimes I rehearse conversations in the shower. I always win.","It's weird how the same sun shines on all of us. Except when it's cloudy.","I bet you're wondering why I'm standing here. So am I.","I'd like to thank the sidewalk for always being there.","I eat cereal for dinner. It's called self-care.","Once I saw a man juggle chainsaws. He dropped one. Don't ask.","I feel like I've forgotten something. Probably my wallet. Or my dignity.","I wonder how many steps I've taken in my life. Too many, by my feet.","There's a guy in my building who only speaks in riddles. I hate him.","The moon was really bright last night. Showoff.","I bought a book on procrastination. I'll read it later.","If you stare at a pigeon long enough, it stares back.","I don't have a problem. I have a hobby. Of staring at stuff.","I think hot dogs are just sausages in disguise.","A man gave me a free sample today. I'm still thinking about it.","People who don't use turn signals fascinate me. Scientific interest.","I found a penny today. Now I'm rich. Look out, world.","I tried yoga once. Pulled a muscle in my pride.","Why do they put ketchup in the fridge? It's already in a bottle.","I had a dream I was a taco. Delicious but exhausting.","If I won the lottery, I'd buy a boat. And hire a captain. And never go on it.","That bird just looked at me like I owe it rent.","Sometimes I imagine the traffic lights are having a conversation.","I stepped in gum yesterday. Now I'm sticky and philosophical.","Sometimes I think a lot. Then I take a nap.")
POOL(EN_absurd, "My toaster owes me money.","I'm 40% pigeon on my mother's side.","Beep boop. I'm a robot. Just kidding. Maybe.","I once argued with a vending machine and lost.","The moon sent me a postcard.","I can talk to squirrels. They never answer.","My shadow quit last week. I'm still processing it.","I'm allergic to Mondays. And Tuesdays. And nouns.","Last night I dreamed I was a sandwich. Woke up hungry.","There's a goose that follows me. I call him Steve.","I'm on a first-name basis with the ATM.","My neighbor's cat has a better credit score than me.","I once got a parking ticket for a bicycle that wasn't mine.","I'm not saying I'm a wizard, but my socks keep disappearing.","Somewhere, a cow is thinking about me.","I haven't blinked in a week. Don't test me.","My left foot has opinions about politics.","I speak fluent mumble.","I've been struck by lightning twice. Both times metaphorically.","My refrigerator hums my favorite song.","If I yell loud enough, the wind listens.","The mailman and I are in a feud. Nobody knows why.","I invented a new color. It's called 'ohm'.","I'm the world champion of nothing in particular.","I think the clouds are going to the same place as me.","I once convinced a pigeon to attend a meeting.","My spoon is cursed. Don't ask.","I'm not lost, I'm exploring emotionally.","Yesterday I found out my reflection is left handed. Suspicious.","I have a PhD in staring at traffic.","I've been blessed by a seagull. Is that lucky?","I took a nap on a skateboard once. Don't recommend.","Tuesday smells like crayons.","My hat is smarter than I am.","The grass is plotting something.","I tried to high five a ghost. Cold hands.","Somewhere out there, my twin is eating a better sandwich.","I tip my hat to every lamppost I pass. They never tip back.","I'm 6 feet tall in dog years.","Every night at 3 AM my pillow whispers 'taxes'.","I'd marry a burrito if it asked nicely.","I whistled at a statue today. It ignored me.","A raccoon taught me everything I know.","Never underestimate a man in sandals.","I walked into a glass door. The door apologized.","If I vanish, check the nearest taco truck.","I tried to buy happiness at the store. Out of stock.","The wind told me a secret. It was mostly 'whoooo'.","I've never met a cactus I didn't want to hug.","Some say I'm a legend. Those some are my cousins.","I have a mortal enemy: the revolving door.","The ducks and I have an agreement. I don't ask, they don't tell.","I'm legally required to say this: bing bong.","Banana. That's it. That's the thought.","My brain is a browser with 83 tabs open.","I keep seeing the number 7. Is it following me?","I can't feel my elbow, but I can feel the tension.","My soul left for lunch and didn't come back.","I bet clouds are just sleeping ghosts.","I once saw a squirrel wearing a tiny hat. Or I hallucinated. Either way, cute.","Zebras are horses in prison stripes. Think about it.","I've seen things you people wouldn't believe. Mostly receipts.","Bzzzzt. System rebooting. Just kidding. I'm just tired.","Wubba lubba dub dub. I don't know what it means either.","My uncle is a lighthouse. Long story.","I once traded my left shoe for a ukulele. Best deal ever.","I'm kind of a big deal. In my own head.","A fish told me to follow my dreams. It was hungry though.")
POOL(EN_mumble, "La la la la...","Hmm hmm hmm.","*humming quietly*","Mm. Mmm. Mmmm.","Do dee doo...","Hum de dum...","Ba ba ba, ba ba ba, bum.","Pfft.","*sighs*","Hmm... where did I put it?","Right. Left. Right. Left.","Nope. Not that one. Nope.","*whistles off-key*","Hup, hup, hup.","Uh-huh. Mm-hm.","Ohhh boy.","Whoo... okay...","Oh dear.","Hah. Hah. Ha. Ha.","Tra la la...")
POOL(EN_sp_greet, "Hey, you! Yeah, you!","Hello there!","Oh hi!","Yo!","Hey, nice day, huh?","What's up?","Well, hello stranger.","Hi, friend!","Hey! You look familiar. Or not.","Howdy, partner.","Excuse me, got a second?","Hey, hey! Over here!","Nice to see someone out here.","Hello! I'm {n}. Hi!","Oh, hey, don't mind me.")
POOL(EN_sp_insult, "Nice outfit. Did you lose a bet?","Out of my way, loser!","What are you staring at, huh?","You walk like a confused duck.","Move it, slowpoke!","Hey, watch it, genius!","You smell like regret and onions.","Lost your manners, did you?","What a hairstyle. Is it intentional?","You call that a walk?","Look at this guy. Just look at him.","Don't you have somewhere better to be? Anywhere?","Oh great. You.","Wow, you really are something. I'm not sure what.","Do you do that on purpose? The face?")


// ===================== INDONESIA =====================
POOL(ID_greet, "Halo juga, bro!","Yo, ada apa?","Eh, orang baru ya?","Hai! Lagi jalan-jalan?","Woi, apa kabar?","Halo, halo!","Pagi, bro.","Wih, ada tamu.","Santai aja, gua {n}.","Halo! Cuacanya enak ya.","Hei, lu nyasar?","Salam kenal, bro!","Ada yang bisa gua bantu?","Yoi! Apa kabar?","Eh, halo! Gua lagi ngelamun tadi.","Hai, hai!","Mantap, ada yang nyapa.","Hola, amigo! Eh, maksudnya halo.","Oh hai. Gua kira lu patung.","Halo juga, sob.","Yo, ada perlu apa, bro?","Halo, halo, selamat datang di trotoar gua.","Eh, lu lagi ngapain di sini?","Wih, muka baru nih.","Halo juga! Santai aja, gua nggak gigit.","Hai! Gua baru aja mikirin lu. Bohong sih.","Pagi, siang, sore, malam, pokoknya halo.","Oh, hai. Gua kira lu orang lain.","Salam kenal ya, jangan malu-malu.","Hei! Ada yang bisa dibantu, bos?","Eh, halo. Lu keliatan kayak orang baik.","Yo, apa kabar dunia?","Selamat datang, sob!","Hai, gua {n}. Lu siapa?","Waduh, ada orang. Halo!","Halo juga. Cuacanya lumayan ya?","Hei, lu yang tadi lewat sini kan?","Gimana-gimana? Ada kabar baru?")
POOL(ID_greet_angry, "Apa? Gua lagi nggak mood.","Cepetan, gua sibuk.","Hmph. Ada perlu apa?","Mau apa lu?","Jangan ganggu gua.","Gua lagi kesel. Singkat aja.","Ngapain liat-liat?","Nggak ada waktu buat basa-basi.")
POOL(ID_greet_scared, "H-halo... lu nggak bakal macam-macam kan?","Halo. Gua cuma lewat doang, bro.","Eh! Lu bikin gua kaget.","H-hai... aman kan di sini?","Halo... jangan deket-deket ya.","Gua nggak mau masalah, serius.")
POOL(ID_greet_happy, "Halo juga! Hari yang bagus ya!","Woy! Senang ketemu lu!","Hai! Ada yang bisa gua bantu?","Wih, mood gua lagi bagus nih! Halo!","Yoo, sob! Gimana kabarnya?","Hai hai! Hari ini indah banget!","Halo! Lu bikin hari gua makin asik!")
POOL(ID_howare_angry, "Buruk. Hari ini bikin emosi terus.","Jangan nanya, lagi bete banget gua.","Kesel. Udah itu aja.","Nggak baik. Nggak usah dibahas.","Rasanya pengen ngamuk. Serius.","Kesel gua dari pagi, jangan tambahin.","Buruk. Jangan nanya lagi.","Lagi pengen nonjok tembok, jadi nggak baik.","Nggak baik, dan lu nggak bantu.")
POOL(ID_howare_scared, "Agak tegang, bro. Daerah ini kadang nggak aman.","Gua... baik-baik aja. Cuma waspada.","Gemeteran gua. Serius.","Jantung gua deg-degan terus.","Nggak tenang gua, bro.","Gua gelisah banget, bro.","Tangan gua gemeteran dari tadi.","Perasaan gua nggak enak terus.","Nggak tenang, kayak ada yang ngikutin.")
POOL(ID_howare_happy, "Mantap banget hari ini!","Baik banget, bro! Lu sendiri gimana?","Lagi bagus nih, nggak ada yang bikin pusing.","Alhamdulillah, lancar jaya!","Luar biasa! Gua nemu duit seribu tadi.","Seneng banget gua hari ini!","Lagi bagus banget, sumpah!","Hari ini gua lagi di atas awan!","Senang banget, bro, entah kenapa!","Mood gua lagi tinggi-tingginya!")
POOL(ID_howare, "Biasa aja, bro. Hidup jalan terus.","Yaa gitu-gitu aja. Lu sendiri?","Lumayan lah, masih bisa napas.","Capek, tapi masih bisa ketawa.","Nggak buruk, nggak bagus juga.","Hidup itu kayak sinyal, kadang ada kadang nggak.","Baik. Kaki gua pegel doang.","Santai aja. Lu gimana?","Gini-gini aja, bro. Lu sendiri?","Lumayan lah, belum mati.","Kadang bagus, kadang nggak. Hari ini ya gitu deh.","Baik-baik aja, cuma dompet yang nggak baik.","Alhamdulillah masih bisa nongkrong.","Nggak ada yang spesial, bro.","Kayak biasa. Capek tapi jalan terus.","Cukup baik buat ngobrol sama lu.","Gua oke. Perut gua yang nggak.","Hidup lagi lempeng-lempeng aja.","Jalan terus, bro, mau gimana lagi.","Mendingan dari kemarin.")
POOL(ID_name, "Nama gua {n}. Lu sendiri?","Panggil aja gua {n}, bro.","{n}. Orang sini, udah lama nongkrong.","Gua {n}. Kenapa, mau bikin buku?","{n}. Jangan dilupain ya.","Nama gua {n}. Salam kenal!","Orang-orang manggil gua {n}.","{n}. Ngomong-ngomong lu siapa?","Gua {n}, bukan siapa-siapa.","Orang manggil gua {n}, tapi lu boleh manggil apa aja.","Nama gua {n}. Panjang ceritanya.","{n}! Inget ya, nanti gua tagih.","Gua {n}. Kalau lupa, tanya lagi aja.","Panggil {n} aja, nggak usah formal.","{n}, anak sini. Lu?","Namanya {n}. Bagus kan? Orang tua gua yang milih.")
POOL(ID_thanks, "Sama-sama, bro!","Santai aja.","Hehe, bisa aja lu.","Nggak masalah!","Siap, kapan-kapan lagi ya.","Gua senang bisa bantu.","Udah, jangan sungkan.","Sama-sama! Nah gitu dong, yang sopan.","Sama-sama, bro, santai aja.","Gua yang makasih udah ngajak ngobrol.","Ah, jangan sungkan.","Nggak usah makasih, cukup traktir kopi.","Sip, sama-sama!","Gua cuma bantu dikit.","Hehe, kapan-kapan gantian ya.","Wah, jarang ada yang bilang makasih.","Udah, kita kan temen.","Siap, bos, kapan aja.")
POOL(ID_bye, "Oke, hati-hati di jalan.","Yoi, sampai ketemu lagi!","Cabut aja, gua juga mau jalan.","Dadah, bro!","Jaga diri ya.","Sampai jumpa, sob.","Oke, jangan lama-lama ilang.","Hati-hati ya, jangan nyasar.","Oke, hati-hati ya, jangan ngebut.","Sampai nanti, bro!","Duluan ya! Jangan kangen.","Yoi, ketemu lagi ntar.","Dadah! Salam buat keluarga.","Jaga diri, sob.","Pamit dulu? Oke, hati-hati.","Sana gih, jangan lupa pulang.","Bye bye! Jangan nyasar.","Sampai ketemu lagi, kawan.")
POOL(ID_sorry, "Yaudah, nggak apa-apa.","Santai, gua maafin.","Oke, kita impas.","Udah lupain aja.","Makasih udah minta maaf.","Nggak masalah, bro.")
POOL(ID_yes, "Nah, itu dia!","Setuju gua!","Betul banget.","Yoi, sepakat.","Mantap, kita sepemikiran.","Bagus, bagus.")
POOL(ID_no, "Yah, kok gitu?","Yaudah, terserah lu.","Wah, sayang banget.","Oke, gua nggak maksa.","Hmm, rugi lu.","Yaudah deh.")
POOL(ID_money, "Duit? Gua juga lagi seret nih.","Lagi nggak ada, bro. Coba tanya orang lain.","Gua aja kekurangan!","Dompet gua lagi diet.","Minjem duit? Gua trauma.","Cuma ada receh dan permen.","Kerja dong, bro. Eh, bercanda.","Gua lagi nabung buat makan.","Duit itu fana, bro. Tapi tetep butuh.","Gua lagi bokek berat, bro, serius.","Minjem duit? Gua aja minjem.","Duit gua tinggal di saku celana yang kemarin.","Nggak ada, bro, tanggal tua.","Gua kasih doa aja ya, gratis.","Dompet gua isinya struk doang.","Lu salah orang, gua lebih miskin dari lu.","Kerja dulu sana, nanti gua traktir.","Duit? Gua cuma punya mimpi.","Tanya bank, bukan gua.","Gua nabung buat beli sandal baru.","Duit itu cuma kertas, tapi kok susah dicari ya.")
POOL(ID_directions, "Wah, gua kurang tau daerah situ.","Lurus aja terus, nanti juga ketemu. Kayaknya.","Gua cuma tau jalan sekitar sini, bro.","Belok kiri, terus kanan, terus... lupa.","Tanya orang lain deh, gua bukan GPS.","Ikutin bau tacos, pasti ketemu.","Sebelah sana, deket yang itu, yang ada itunya.","Gua juga sering nyasar.","Wah, gua juga nggak tau, bro.","Lurus terus, belok kanan di pohon besar.","Tanya orang lain deh, gua gampang nyasar.","Ikutin aja jalan ini, nanti juga ketemu.","Kayaknya deket sini, tapi gua nggak yakin.","Coba cek peta, jangan tanya gua.","Belok kiri dua kali, terus pasrah.","Setau gua sih ke arah sana. Setau gua lho.","Jauh sih, naik apa lu?","Deket kok, tinggal jalan tiga menit. Atau tiga puluh.","Gua cuma tau warung di ujung jalan.","Ikutin kerumunan, biasanya ke sana.")
POOL(ID_love, "Hahaha, lu ada-ada aja!","Wah, jangan bikin gua baper, bro.","Hehe, gombalan lu lumayan lucu.","Cieee.","Gua udah ada yang punya. Namanya tacos.","Pelan-pelan dong, baru kenal.","Aduh, gua jadi malu.","Traktir makan dulu baru ngomong.","Waduh, gombalan lu level berapa nih?","Jangan bikin gua salting, bro.","Gua tersanjung, tapi gua bingung.","Hahaha, lu lucu juga.","Pelan-pelan, kenalan dulu.","Gua udah punya cinta, namanya nasi goreng.","Wih, berani juga lu.","Aduh, mukanya jadi merah nih.","Hati gua udah diisi kopi.","Gombalannya klasik tapi lumayan.")
POOL(ID_compliment, "Makasih, gua usaha.","Hehe, gua terima.","Lu juga keren, bro.","Wah, jadi malu gua.","Bisa aja lu!","Akhirnya ada yang ngerti.","Pujian lu bikin hari gua bagus.","Makasih, bro. Serius.","Wah, makasih, hari gua jadi bagus.","Lu juga keren, jujur.","Hehe, gua jadi geer.","Bisa aja lu, bro.","Pujian lu bikin gua melayang.","Makasih, gua catat di buku harian.","Lu orangnya baik ya.","Gua tersipu nih.","Wow, tumben ada yang muji.","Terima kasih, jangan berhenti ya.")
POOL(ID_insult, "Mulut lu, dijaga!","Ngaca dulu, baru ngatain orang!","Santai dikit napa, bro.","Wah, kasar banget.","Gua nggak salah apa-apa sama lu.","Hidup lu stres banget kayaknya.","Ngomong sekali lagi, gua bikin lu nyesel!","Nggak ada sopan-santunnya lu.","Yaelah, bawa-bawa gua ke hari buruk lu.","Gua pergi aja deh kalau lu begitu.","Eh, jaga omongan lu.","Lu ngomong apa tadi? Ulangin.","Mulut lu perlu disekolahin.","Gua nggak ada urusan sama lu, kenapa nyolot?","Hati-hati ngomong, bro.","Lagi nyari masalah ya?","Santai napa, hidup lu stres amat.","Lu kayaknya salah bangun tidur.","Ngatain orang kok semangat banget.","Hari lu pasti buruk, ya. Ngerti kok.","Gua diem bukan berarti takut.","Lu bikin gua sedih, tau nggak?")
POOL(ID_threat, "Wah, santai bro. Jangan cari masalah.","Gua panggil polisi nih kalau lu ngancem terus!","J-jangan! Gua cuma lewat doang!","Coba aja kalau berani.","Tolong... jangan sakitin gua!","Lu pikir gua takut? Hah!","Hei hei, ngomong yang bener.","Oke oke, gua pergi sekarang!","Wah wah, santai dong, jangan gitu.","Gua nggak mau ribut, serius.","Jangan nyakitin gua, gua cuma lewat!","Coba aja, gua nggak takut!","Lu serius? Gua panggil polisi nih!","Tenang, tenang, kita ngobrol baik-baik.","Gua nggak punya salah sama lu!","Oke, oke, gua nyerah, jangan apa-apain!","Berani lu sama gua? Hah?","Jangan macem-macem ya.","Gua pergi sekarang, jangan ikutin.")
POOL(ID_joke, "Kenapa ayam nyebrang? Biar sampai seberang.","Kenapa sapi nggak bisa main internet? Takut digembok.","Apa bedanya lu sama kulkas? Kulkas nggak ngomong.","Ikan apa yang bisa nyanyi? Ikan paus. Paus lagi nyanyi.","Gua tuh orangnya setia. Kayak hutang.","Kenapa angka tiga takut? Soalnya tiga dua satu.","Apa yang lebih panjang dari sepuluh meter? Sebelas meter.","Gua bukan pelit, gua hemat. Bedanya setipis tisu.","Kenapa kuburan nggak pernah sepi? Soalnya banyak yang antri.","Apa bedanya kopi sama jodoh? Kopi bisa diseduh, jodoh susah diseduh.","Kenapa gajah nggak bisa main HP? Jarinya kegedean.","Ada orang jual bubur, tapi jualnya malem. Namanya bubur lembur.","Kenapa programmer suka kopi? Biar nggak kena error pas ngantuk.","Kenapa polisi tidur nggak bisa nangkep maling? Soalnya lagi tidur.","Ayam goreng lagi sedih, soalnya dia merasa digoreng terus.","Siapa yang paling sabar? Tukang parkir. Nunggu terus.","Gua tuh nggak malas, cuma hemat energi.","Kenapa jam dinding nggak pernah capek? Soalnya selalu digantung.")
POOL(ID_weather, "Cuacanya aneh akhir-akhir ini, ya?","Panas banget. Kenapa sih?","Kayaknya mau hujan. Lutut gua bilang gitu.","Langitnya cerah, mantap.","Dingin-dingin gini enaknya makan mi.","Hujan bikin kota kerasa lebih bersih.","Cuacanya cocok buat tidur. Selalu cocok buat tidur.","Awannya mirip bebek hari ini.")
POOL(ID_food, "Gua laper banget, serius.","Pizza jawabannya. Pertanyaannya nggak penting.","Tacos. Selalu tacos.","Kopi dulu, baru bisa mikir.","Hot dog pinggir jalan itu gourmet.","Burger enak, tapi mi lebih enak.","Gua bisa makan sepiring sendirian.","Ayam goreng itu makanan terbaik. Debat sama gua.","Gua ngidam nasi goreng, bro.","Makan apa ya enaknya? Semua kayaknya enak.","Kopi dulu sebelum mikir apa pun.","Pizza itu makanan kemenangan.","Gua lapar dari tadi pagi, serius.","Ada warung enak di deket sini, kalau gua inget.","Mie instan itu penyelamat akhir bulan.","Taco itu makanan para dewa.","Gua bisa makan lima porsi, sumpah.","Sambel dulu, baru makanan.","Es teh manis itu ibadah.")
POOL(ID_music, "Gua suka rap sama rock, semua suka.","Nyalain radio, bro, pasti ada lagu enak.","Gua nyanyi di kamar mandi. Tetangga protes.","Musik bikin semuanya lebih baik.","Gua nggak bisa nari, tapi gua berani.","Lagu favorit gua yang lagi main sekarang.","Lagu lama itu emas, bro.","Bass itu detak jantung kota.")
POOL(ID_cars, "Mobil lu keren. Punya gua kayak kursi malas jalan.","Bensin mahal, bro. Perampokan di siang bolong.","Gua pernah nyetir mundur tiga kilometer.","Lowrider itu seni berjalan.","Mobil gua penuh karakter. Kebanyakan karat.","Motor lebih asik, nggak macet.","Parkir paralel itu tes kepribadian.","Mesinnya bagus, supirnya yang bermasalah.")
POOL(ID_police, "Polisi? Jangan mulai deh.","Mending nunduk aja kalau ada polisi.","Gua belum pernah ditangkap. Sebagian besar.","Sirene bikin gua deg-degan.","Jaga diri, bro, polisi di mana-mana.","Gua warga biasa. Biasa banget.","Hukum itu bagus. Dari jauh.","Gua takut sama kertas kerjanya, bukan polisinya.")
POOL(ID_gang, "Geng? Gua urus urusan gua sendiri.","Warna baju penting di sini. Hati-hati.","Dulu sini tenang. Dulu.","Jangan masuk wilayah orang, bro.","Gua netral. Kayak Swiss, tapi makanannya lebih jelek.","Hormat itu lebih jauh dari pistol.","Denger tembakan malam-malam? Abaikan aja.","Teman itu bagus, damai lebih bagus.")
POOL(ID_work, "Kerja? Jangan ingetin gua.","Bos gua kayak mimpi buruk kecil yang berisik.","Gua lagi nganggur. Enam tahun.","Pengen resign, tapi tagihan kangen.","Gua nganter pizza. Enak kalau masih panas.","Kerja keras, tidur lebih keras.","Gaji kecil, mimpi besar.","Impian gua: tukang tidur profesional.")
POOL(ID_family, "Keluarga itu ribet. Punya gua lebih ribet.","Ibu gua bakal marah kalau liat gua di sini.","Kakak gua utang duit sama sepotong sandwich.","Makan malam keluarga itu medan perang pakai kuah.","Gua sayang keluarga gua, dari jauh.","Nenek gua bisa ngalahin siapa aja.","Keluarga nomor satu. Camilan nomor dua.","Om gua ceritanya itu-itu aja tiap lebaran.")
POOL(ID_age, "Cukup tua buat tau, cukup muda buat nggak peduli.","Dua puluh sembilan. Atau tiga puluh sembilan. Lupa.","Umur cuma angka. Angka yang ngeselin.","Hati gua dua puluh, lutut gua delapan puluh.","Jangan nanya umur. Atau berat badan. Atau mantan.","Tiga puluhan. Entahlah.")
POOL(ID_from, "Gua lahir dan gede di Los Santos.","Gua dari luar kota. Kangen tiap hari.","Gua pindah ke sini buat cuaca. Ternyata asap.","Gua dari kota kecil yang nggak lu kenal.","Gua dari Ganton. Masih di sini.","Gua ke sini bawa mimpi. Dapatnya macet.")
POOL(ID_time, "Gua nggak punya jam, tanya matahari.","Kayaknya udah waktunya makan siang.","Waktu itu relatif. Punya gua biasanya salah.","Cek HP lu dong, genius.","Entah. Pagi atau malam, sama aja buat gua.","Jam berapa ya? Pokoknya sekarang.")
POOL(ID_help, "Ada apa? Cepetan.","Bantu? Gua nggak jago, tapi gua coba.","Telepon 911, bro. Gua bukan dokter.","Tenang dulu, ceritain semuanya.","Gua bisa ngasih dukungan moral. Plus setengah sandwich.","Oke oke, gua di sini. Ada apa?")
POOL(ID_sleep, "Tidur? Apaan tuh? Gua lupa.","Gua ngantuk banget, bisa tidur sambil berdiri.","Kasur itu penemuan terbaik.","Insomnia itu nyebelin banget.","Gua mimpiin tacos tiap malam.","Tidur siang itu waktu favorit gua.")
POOL(ID_games, "Game? Gua suka banget.","Gua stuck di level tiga. Setahun.","Gua gamer santai. Santai, tapi emosian.","Konsol mahal, stik melayang.","Lu main apa? Gua penasaran.","Main game bikin waktu hilang. Waktu gua doang.")
POOL(ID_question, "Pertanyaan bagus. Gua belum pernah mikirin itu.","Susah dijawab, bro. Menurut lu sendiri gimana?","Entahlah. Mungkin iya, mungkin enggak.","Kenapa nanya gua? Gua keliatan pinter?","Itu di atas gaji gua.","Pertanyaan sejuta dolar, itu.","Nanti gua pikirin, terus nggak gua kasih tau.","Kayaknya iya. Mungkin enggak. Tergantung.","Gua pass dulu.","Jawabannya empat puluh dua. Selalu.","Hmm, gua belum pernah ditanya gitu.","Susah juga ya. Menurut lu gimana?","Gua nggak yakin, tapi kayaknya iya.","Pertanyaan lu dalem banget buat jam segini.","Wah, gua nggak tau jawabannya.","Entahlah, tanya lagi besok.","Kok lu nanya gua? Gua kan cuma lewat.","Jawabannya ada di dalam hati. Atau di internet.","Gua nggak ahli soal itu.","Itu pertanyaan jebakan, ya?")
POOL(ID_default_angry, "Udah, jangan ganggu gua lagi.","Gua lagi nggak mood. Pergi sana.","Hmph. Terserah lu.","Bodo amat.","Nggak minat.","Pergi aja deh.","Jangan bikin gua makin kesel.","Itu urusan lu, bukan gua.","Gua nggak peduli.","Nggak penting buat gua.","Udah ya, gua nggak mau denger.","Berisik.","Capek gua ngomong sama lu.","Lu ganggu banget.")
POOL(ID_default_scared, "J-jangan deket-deket ya, bro...","Lu bikin gua nggak nyaman.","Gua mending pergi aja.","Gua nggak tau apa-apa, serius.","Perasaan gua nggak enak.","Jantung gua mau copot.","Jangan noleh ke belakang. Serius.","Gua mau pulang aja.","G-gua nggak tau apa-apa.","Tolong jangan macem-macem.","Ada yang aneh di sini.","Gua takut, bro.","Jangan liatin gua gitu.")
POOL(ID_default_happy, "Hahaha, bisa aja lu!","Santai, bro. Hidup itu indah!","Wih, seru juga ngobrol sama lu.","Gua suka ngobrol sama lu, sumpah.","Hari ini bagus banget!","Ayo ngerayain sesuatu! Apa aja!","Lu orangnya asik, tau nggak?","Gua pengen nyanyi nih!","Hahaha, seru banget!","Wih, mantap!","Lu lucu banget, tau nggak?","Gua suka ngobrol sama lu!","Aduh, gua ketawa terus.","Lu bikin hari gua indah!")
POOL(ID_default, "Hmm, gitu ya.","Oke, oke. Terus?","Menarik juga omongan lu.","Gua dengerin kok. Lanjut.","Yaa gitu deh jalan hidup.","Iya, iya.","Bisa jadi.","Wah, gitu ceritanya.","Gua nggak tau soal itu.","Hmm, masuk akal. Kayaknya.","Terserah lu deh.","Oh begitu.","Hidup itu misteri. Sama kayak sandwich.","Lu ngomong apa sih? Tapi seru.","Oh gitu.","Ya ampun.","Terus gimana?","Gua nggak ngerti, tapi seru.","Wah, menarik.","Beneran?","Gitu ya ceritanya.","Hmm, lanjut, gua dengerin.","Aneh juga ya.","Wah, kok bisa?","Haha, oke deh.","Serius lu?","Duh, gua jadi mikir.","Nggak nyangka gua.")
POOL(ID_random, "Gua curiga awan itu ngikutin gua.","Burung merpati itu drone pemerintah.","Kaos kaki kiri gua ilang lagi. Konspirasi.","Pernah nggak lu bengong ngeliatin tembok?","Gua penasaran bebek mikirin apa tentang kita.","Kenapa bangunan disebut bangunan padahal udah dibangun?","Gua ngomong sendiri. Normal nggak sih?","Trotoar ini hangat, kayak selimut raksasa yang ngebosenin.","Gua udah kasih nama semua merpati di jalan ini.","Kadang gua jalan mundur biar orang bingung.","Manusia itu aneh. Gua manusia.","Kunci gua ilang lagi, padahal di tangan.","Hari ini gua jadi figuran, bukan tokoh utama.","Gua makan sereal buat makan malam. Namanya perawatan diri.","Ada kucing di atap itu ngeliatin gua kayak nagih utang.","Gua nemu koin tadi. Sekarang gua kaya.","Gua pernah kejebak di pintu putar sejam.","Tikus itu bawa pizza. Respek.","Gua nggak punya masalah, gua punya hobi: bengong.","Kalau gua jadi sayuran, gua jadi kentang. Setia tapi biasa.","Kenapa ya hari Senin selalu datang cepet?","Gua penasaran, semut punya hari libur nggak ya?","Kadang gua mikir, awan itu lagi ngapain.","Pernah nggak lu merasa ditatap sama patung?","Kucing itu pasti punya rahasia besar.","Gua rasa lampu merah itu suka ngerjain gua.","Gua pengen punya hammock, di mana aja.","Hidup tuh kayak sinyal, kadang penuh kadang nol.","Tukang bakso tadi senyum ke gua. Mencurigakan.","Gua baru sadar, kaos kaki itu selalu berpasangan, kecuali yang ilang.","Kenapa roti bentuknya kotak, tapi ngenyangin bulat?","Besok gua mulai diet. Besoknya lagi juga.")
POOL(ID_absurd, "Pemanggang roti gua ngutang duit sama gua.","Gua 40 persen merpati dari pihak ibu.","Bip bop. Gua robot. Bercanda. Mungkin.","Gua pernah berantem sama mesin minuman dan kalah.","Bulan ngirim kartu pos buat gua.","Bayangan gua resign minggu lalu.","Gua alergi hari Senin, Selasa, dan kata benda.","Ada angsa yang ngikutin gua, namanya Steve.","Kucing tetangga skor kreditnya lebih bagus dari gua.","Kulkas gua ngedengungin lagu favorit gua.","Gua pernah diceramahin merpati. Dia benar.","Otak gua itu browser dengan 83 tab kebuka.","Jiwa gua pergi makan siang dan nggak balik.","Pisang. Itu aja. Itu pikiran gua.","Gua bisa makan satu burrito sekali telan.","Wubba lubba dub dub. Gua juga nggak ngerti.","Gua pernah diajak debat sama kulkas. Gua kalah.","Sendok gua punya dendam sama gua.","Tadi malam gua mimpi jadi kentang goreng.","Ayam tetangga bisa nyanyi dangdut.","Bantal gua suka berbisik pas tengah malam.","Gua punya musuh bebuyutan: pintu putar.","Mobil gua bunyi 'tuing' tiap ketemu polisi.","Gua yakin tikus itu punya ijazah.","Tadi gua ngomong sama pohon, dia jawab.","Gua alergi sama kata 'besok'.")
POOL(ID_mumble, "La la la la...","Hmm hmm hmm.","*bersenandung pelan*","Mm. Mmm. Mmmm.","Tralala...","*menghela napas*","Oalah.","Hadeh.","Aduh, di mana ya tadi...","*bersiul fals*")
POOL(ID_sp_greet, "Woi, lu!","Halo!","Eh, hai!","Yo!","Hei, cuacanya bagus ya?","Apa kabar?","Halo, orang asing.","Hai, sob!","Maaf, ada waktu sebentar?","Hei hei, di sini!","Gua {n}, halo!","Eh, permisi, bentar!","Hei, lu yang di sana!","Halo, boleh ganggu sebentar?","Yo, bro, apa kabar?","Woi, sini sini!","Pagi, bro!","Eh, kenalan dong.")
POOL(ID_sp_insult, "Bajunya bagus. Kalah taruhan ya?","Minggir, pecundang!","Liat apa lu, hah?","Jalan lu kayak bebek bingung.","Cepetan dong, lambat banget!","Hei, awas, genius!","Mukanya sengaja ya begitu?","Wah, rambut lu. Sengaja?","Lu nggak ada tempat lain?","Dasar kampungan.","Minggir, jalanan bukan punya lu!","Baju lu kayak dapet dari tong sampah.","Ngapain lu berdiri di situ, patung?","Jalan yang bener dong!","Lu bau bawang, tau nggak?","Dasar lamban!","Awas, jangan halangin gua!","Norak banget sih lu.")

// ===================== SPANYOL (inti) =====================
POOL(ES_greet, "¡Hola, amigo!","¿Qué onda, hermano?","Buenas, ¿todo bien?","¡Ey! ¿Qué tal?","¡Hola! ¿Te perdiste?","Buenos días, compa.","¿Qué hubo?","¡Saludos, ciudadano!","Hola, hola, ¿cómo andas?","¡Oye! ¿Eres nuevo por aquí?")
POOL(ES_greet_angry, "¿Qué quieres?","Rápido, estoy ocupado.","No estoy de humor.","Hmph. ¿Necesitas algo?","¿Qué miras?")
POOL(ES_greet_scared, "H-hola... no vas a causar problemas, ¿verdad?","Solo estoy de paso, hermano.","¡Ay! Me asustaste.","Hola... por favor, calma.")
POOL(ES_greet_happy, "¡Hola! ¡Qué buen día!","¡Ey, amigo! ¡Qué gusto verte!","¡Hola, hola! ¿Cómo estás?","¡Qué onda! ¡Hoy todo va bien!")
POOL(ES_howare_angry, "Mal. Hoy todo me sale mal.","No preguntes. Estoy de mal humor.","Fatal. Siguiente pregunta.")
POOL(ES_howare_scared, "Nervioso, hermano. Muy nervioso.","Bien... solo vigilando.","Esta zona no siempre es segura.")
POOL(ES_howare_happy, "¡Muy bien, amigo! ¿Y tú?","¡Fantástico! Hoy encontré un dólar.","Todo perfecto, sin quejas.")
POOL(ES_howare, "Aquí, sobreviviendo. ¿Y tú?","Bien, no me quejo.","Más o menos, ya sabes cómo es.","Cansado, pero de pie.","Normal, compa.")
POOL(ES_name, "Me llamo {n}. ¿Y tú?","Soy {n}, mucho gusto.","Llámame {n}.","{n}, para servirte.","Me dicen {n}. Pero tú puedes decirme {n}.")
POOL(ES_thanks, "¡De nada, amigo!","Para eso estamos, hermano.","No hay de qué.","Con gusto.","¡A ti, compa!")
POOL(ES_bye, "Cuídate mucho.","Nos vemos, amigo.","Hasta luego.","Adiós, compa.","Que te vaya bien.","Hasta la vista.")
POOL(ES_sorry, "No pasa nada.","Está bien, olvídalo.","Disculpa aceptada.","Tranquilo, amigo.")
POOL(ES_yes, "¡Exacto!","Eso mismo.","Así es.","Claro que sí.")
POOL(ES_no, "Qué lástima.","Como quieras.","Bueno, tú sabrás.","Ni modo.")
POOL(ES_money, "No tengo dinero, hermano. Lo siento.","Estoy en la quiebra, amigo.","¿Dinero? Yo también ando sin nada.","Mi cartera está a dieta.","Pídele a otro.")
POOL(ES_directions, "Lo siento, no soy de aquí.","Sigue derecho, ya lo encontrarás. Creo.","Solo conozco esta cuadra, hermano.","Por ahí, cerca de la cosa con la otra cosa.")
POOL(ES_love, "¡Jaja, qué atrevido!","Me vas a hacer sonrojar.","Primero invítame a cenar.","Eres muy amable, ¿sabes?")
POOL(ES_insult, "¡Cuidado con lo que dices!","Qué grosero.","Relájate, amigo, no te hice nada.","Mira quién habla.","Qué falta de respeto.")
POOL(ES_threat, "¡Tranquilo, amigo! No quiero problemas.","¡Por favor, no me hagas daño!","¿Quieres pelea? Mala idea.","Llamaré a la policía.","¡Está bien, me voy!")
POOL(ES_joke, "¿Qué le dice un jaguar a otro? Jaguar you.","¿Por qué el libro de matemáticas estaba triste? Tenía muchos problemas.","¿Cuál es el colmo de un electricista? Que su mujer se llame Luz y no lo ilumine.","¿Qué hace una abeja en el gimnasio? ¡Zumba!")
POOL(ES_food, "Tengo hambre, hermano.","Tacos, siempre tacos.","Pizza es la respuesta.","Café primero, pensar después.","Un buen burrito lo arregla todo.")
POOL(ES_question, "Buena pregunta. Nunca lo pensé.","Difícil de decir. ¿Tú qué piensas?","Ni idea, hermano.","Tal vez sí, tal vez no.","Eso está por encima de mi sueldo.")
POOL(ES_default_angry, "No estoy de humor.","Déjame en paz.","Lo que sea.","Ya vete, por favor.")
POOL(ES_default_scared, "Por favor, no te acerques...","No sé nada, lo juro.","Tengo un mal presentimiento.","Mejor me voy.")
POOL(ES_default_happy, "¡Jaja, qué bueno!","La vida es buena, amigo.","Me gusta hablar contigo.","¡Qué día tan bonito!")
POOL(ES_default, "Mmm, ya veo.","Interesante, cuéntame más.","Así es la vida por aquí.","Claro, claro.","¿En serio?","Si tú lo dices.","Puede ser.")
POOL(ES_random, "Creo que esa nube me sigue.","Las palomas son drones del gobierno.","Mi calcetín izquierdo desapareció otra vez.","Me pregunto qué piensan los patos de nosotros.","La acera está tibia, como una manta gigante.","A veces camino hacia atrás para confundir a la gente.","Les puse nombre a todas las palomas de esta calle.")
POOL(ES_absurd, "Mi tostadora me debe dinero.","Soy 40% paloma por parte de mi madre.","Bip bop. Soy un robot. Es broma. Quizás.","Una vez discutí con una máquina expendedora y perdí.","La luna me mandó una postal.","Mi sombra renunció la semana pasada.")
POOL(ES_mumble, "La la la la...","Mmm mmm mmm.","*tarareando*","*suspira*","Ay, ay, ay...")
POOL(ES_sp_greet, "¡Oye, tú!","¡Hola!","¡Ey, amigo!","¿Qué onda?","¡Buenas!")
POOL(ES_sp_insult, "¡Qué ropa! ¿Perdiste una apuesta?","¡Quítate, perdedor!","¿Qué miras, eh?","Caminas como un pato confundido.","¡Fíjate por dónde andas, genio!")

// ===================== POOL BARU: perasaan, pendapat, jenis pertanyaan, gema =====================
POOL(EN_feel_sad, "Aw, man. That sucks. Wanna talk about it?","Hey, it'll get better. It always does. Eventually.","I'm sorry to hear that. Wanna sit down for a minute?","Rough, huh? I've been there.","Chin up, buddy. The sun's still out.","Sadness is just rain for the soul. Or something like that.","Hey, I'm here. Okay, not here here. But I'm listening.","That's tough. Take your time.")
POOL(EN_feel_tired, "Same, man. I could sleep standing up.","You should get some rest. Seriously.","Coffee. Lots of it. Trust me.","Tired is my default setting.","Take a nap. The world can wait.","Ugh, I feel that in my bones.","Go home and sleep, buddy.","I'm tired just hearing it.")
POOL(EN_feel_happy, "Hey, that's awesome! Good for you!","Love that energy! Keep it going!","Happiness looks good on you.","Now that's what I like to hear!","Nice! Let's celebrate. With snacks.","You're glowing, man. Seriously.","Good vibes only!","I'm happy for you. Genuinely.")
POOL(EN_feel_angry, "Whoa, easy there. Take a breath.","Who made you mad? I'll glare at them.","Anger's a heavy bag. Put it down.","Count to ten. Then ten more.","Walk it off, buddy. Walk it way off.","I get it. People can be the worst.","Maybe punch a pillow instead of a person?","Yeah, I'd be mad too.")
POOL(EN_feel_scared, "Hey, it's okay. I'm right here.","Deep breaths. In and out.","What are you scared of? Spiders? Taxes?","You're safe for now. Probably.","Stay close to me. I'm a terrible bodyguard, but still.","Don't worry, I've got your back. Mostly the back part.","Take it slow. One step at a time.","Fear's just excitement that forgot to be fun.")
POOL(EN_feel_bored, "Bored? Same. Wanna stare at a pigeon with me?","Let's do something dumb. That fixes it.","Boredom's the mother of bad ideas. Let's have one.","Go find some trouble. A little. Not too much.","I could tell you a story. A boring one.","Count the clouds. It's a game. Kind of.","Try karaoke. Or don't.","Wanna race to that mailbox?")
POOL(EN_feel_sick, "Ugh, feel better soon. Drink water.","Go see a doctor, man. Seriously.","Soup. Soup fixes everything.","That sounds rough. Get some rest.","Stay warm and hydrate, buddy.","Don't cough on me. Kidding. Maybe.","Hope you're back on your feet soon.","Rest up. Don't be a hero.")
POOL(ID_feel_sad, "Aduh, sabar ya, bro. Mau cerita?","Gua turut sedih. Semua pasti lewat.","Yaelah, sini duduk dulu sebentar.","Berat ya? Gua ngerti kok.","Jangan sedih terus, nanti matahari muncul.","Hidup emang kadang jahat. Tapi lu kuat.","Gua dengerin kok, cerita aja.","Peluk dulu? Bercanda. Kecuali lu mau.")
POOL(ID_feel_tired, "Sama, gua juga capek banget.","Istirahat dulu, bro, serius.","Ngopi dulu, atau tidur sekalian.","Capek itu pengaturan bawaan gua.","Tidur siang aja. Dunia bisa nunggu.","Gua ikut capek dengernya.","Pulang terus tidur, bro.","Pegel-pegel? Pijetin dong. Bercanda.")
POOL(ID_feel_happy, "Wah, seneng banget gua dengernya!","Mantap, pertahankan, bro!","Hari lu pasti indah, ya!","Nah gitu dong, itu yang gua suka!","Ayo ngerayain pakai camilan!","Lu bersinar banget hari ini.","Kabar baik emang obat terbaik.","Gua ikut bahagia, sumpah.")
POOL(ID_feel_angry, "Wah, tarik napas dulu, bro.","Siapa yang bikin lu marah? Gua pelototin dia.","Tenang, tenang, hitung sampai sepuluh.","Jalan-jalan dulu, biar adem.","Tonjok bantal aja, jangan orang.","Gua ngerti, orang kadang nyebelin.","Emosi itu berat, taro dulu.","Gua juga bakal kesel kalau jadi lu.")
POOL(ID_feel_scared, "Tenang, gua di sini.","Tarik napas, buang pelan-pelan.","Takut apa? Hantu? Tagihan?","Lu aman kok. Kayaknya.","Deket gua aja. Gua bodyguard jelek, tapi lumayan.","Santai, satu langkah satu langkah.","Gua jagain, bro. Bagian belakangnya aja.","Takut itu wajar, kok.")
POOL(ID_feel_bored, "Bosen? Sama! Mau ngelamun bareng?","Ayo bikin hal bodoh, itu manjur.","Cari masalah dikit. Jangan banyak-banyak.","Hitung awan, itu permainan. Kayaknya.","Karaokean yuk, atau jangan.","Mau balapan sampai kotak pos itu?","Gua bisa cerita, tapi ceritanya garing.","Bosen itu ibu dari ide jelek. Ayo bikin satu.")
POOL(ID_feel_sick, "Aduh, cepet sembuh ya. Minum air putih.","Ke dokter, bro, serius.","Makan sup, sup nyembuhin segalanya.","Istirahat yang banyak, jangan sok kuat.","Jangan batuk ke gua. Bercanda. Mungkin.","Semoga cepet pulih ya.","Yang hangat-hangat aja dulu, bro.","Tidur, minum obat, jangan main hape.")
POOL(ES_feel_sad, "Ánimo, amigo. ¿Quieres hablar?","Ya pasará, hermano.","Lo siento mucho, de verdad.")
POOL(ES_feel_tired, "Igual yo, hermano.","Descansa un poco.","Un café y a seguir.")
POOL(ES_feel_happy, "¡Qué bueno, amigo!","¡Me alegro por ti!","¡Así me gusta!")
POOL(ES_feel_angry, "Cálmate, hermano.","Respira hondo.","Te entiendo, la gente a veces es lo peor.")
POOL(ES_feel_scared, "Tranquilo, estoy aquí.","Respira, amigo.","Estás a salvo. Creo.")
POOL(ES_feel_bored, "¿Aburrido? Yo también.","Hagamos algo tonto.","Cuenta las nubes.")
POOL(ES_feel_sick, "Que te mejores pronto.","Ve al doctor, amigo.","Sopa, la sopa lo arregla todo.")
POOL(EN_like, "Do I like {w}? Yeah, kind of.","{w}? Honestly, can't stand it.","I love {w}. Don't tell anyone.","{w} is okay. Not my favorite, not my worst.","Ask me about {w} on a better day.","I'm not a big {w} guy, to be honest.","{w}? It's alright. Sometimes it's great.","Love it, hate it, depends on the day. That's {w}.","Yes. No. Maybe. It's {w}, what do you want from me?","{w} changed my life. Not really. But it was fine.","I'm a huge fan of {w}. Okay, a medium fan.","I've had mixed feelings about {w} since forever.","Why do you ask about {w}? Are you selling it?","{w}? Man, don't get me started.")
POOL(ID_like, "Suka {w}? Lumayan sih.","{w}? Jujur gua nggak tahan.","Gua cinta banget {w}. Jangan bilang siapa-siapa.","{w} biasa aja. Bukan favorit, bukan terburuk.","Nanya soal {w} nanti aja pas gua lagi mood.","Gua bukan penggemar {w}, jujur.","{w}? Kadang bagus, kadang nggak.","Suka nggak suka tergantung hari. Itu {w}.","Iya. Enggak. Mungkin. Itu kan {w}, lu maunya apa?","{w} pernah ngubah hidup gua. Bohong. Tapi lumayan.","Gua penggemar berat {w}. Oke, setengah berat.","Gua selalu campur aduk soal {w}.","Kenapa nanya {w}? Lu jualan?","{w}? Wah, jangan mulai deh.")
POOL(ES_like, "¿{w}? Más o menos.","Me encanta {w}, no se lo digas a nadie.","No soy fan de {w}, la verdad.","{w} está bien, ni bueno ni malo.","¿{w}? No me empieces.")
POOL(EN_why, "Because that's just how it is.","Why not?","Nobody knows. Not even the pigeons.","Because life's weird like that.","Good question. Ask the universe.","Because someone said so. Probably my mom.","It's complicated. Mostly dumb, but complicated.","Because gravity. Or taxes. One of those.","Why do you think? Be honest.","Because reasons.")
POOL(EN_how, "Carefully. Very carefully.","With a lot of luck and a little duct tape.","Slowly, then all at once.","Same way everyone does it. Badly.","I'd say just wing it. That's my method.","Step one: panic. Step two: figure it out.","Honestly? No idea. But I'm confident.","By trial and a whole lot of error.","Ask someone smarter. I'll wait.","You just do it. Then complain.")
POOL(EN_when, "Whenever you're ready.","Soon. Or later. Probably later.","Right now. Or in an hour. Time is weird.","When the pigeons say so.","Not today, that's for sure.","When I feel like it. So never.","Yesterday. Wait, no, tomorrow.","Around noon-ish. Or midnight-ish.")
POOL(EN_who, "Nobody important.","Some guy. I forget his name.","My cousin's neighbor's dog, probably.","Who knows? Who cares?","That'd be me. Or someone like me.","A legend. Or a rumor. Can't tell.","I'd tell you, but I forgot.","The guy with the hat. You know the one.")
POOL(EN_what, "Good question. What do you think it is?","Something weird. Possibly a sandwich.","That's the million-dollar question.","Honestly? Beats me.","It's a long story. And a boring one.","Depends who you ask.","A thing. A really important thing.","I'm still figuring that out myself.")
POOL(EN_can, "I could. Will I? That's another question.","Sure. Eventually.","Probably. Don't quote me.","Nope. Not today.","I can do anything. Except fly. And math.","Maybe. What's in it for me?","Depends. Is it dangerous?","I'd love to, but my schedule is full of nothing.")
POOL(EN_do, "Yeah, pretty much.","Nope, not really.","Sometimes. Depends on the day.","Honestly? Yes. And no.","I do. Does that make me weird?","Why do you wanna know?","I used to. Not anymore.","Absolutely. Don't ask me why.")
POOL(ID_why, "Soalnya emang begitu.","Kenapa enggak?","Nggak ada yang tau, merpati juga enggak.","Karena hidup emang aneh.","Pertanyaan bagus. Tanya semesta.","Soalnya ada yang bilang gitu. Mungkin ibu gua.","Ribet. Sebenernya sepele, tapi ribet.","Gara-gara gravitasi. Atau pajak.","Menurut lu kenapa? Jujur aja.","Karena alasan.")
POOL(ID_how, "Hati-hati. Hati-hati banget.","Pakai keberuntungan sama selotip.","Pelan-pelan, lalu tiba-tiba.","Cara semua orang. Dengan jelek.","Asal coba aja, itu metode gua.","Langkah satu: panik. Langkah dua: cari cara.","Jujur? Nggak tau. Tapi gua yakin.","Coba-coba sampai gagal sampai bisa.","Tanya yang lebih pinter, gua tunggu.","Ya dijalanin, terus ngeluh.")
POOL(ID_when, "Kapan pun lu siap.","Sebentar lagi. Atau nanti. Kayaknya nanti.","Sekarang. Atau sejam lagi. Waktu itu aneh.","Pas merpati bilang waktunya.","Bukan hari ini, pasti.","Pas gua lagi mood. Jadi nggak pernah.","Kemarin. Eh, besok.","Sekitar tengah hari. Atau tengah malam.")
POOL(ID_who, "Bukan siapa-siapa penting.","Seorang cowok, gua lupa namanya.","Anjing tetangga sepupu gua, mungkin.","Siapa tau? Siapa peduli?","Gua. Atau yang kayak gua.","Legenda. Atau gosip. Nggak jelas.","Gua kasih tau, tapi gua lupa.","Yang pakai topi itu, tau kan.")
POOL(ID_what, "Pertanyaan bagus. Menurut lu apa?","Sesuatu yang aneh. Mungkin sandwich.","Itu pertanyaan sejuta dolar.","Jujur? Entahlah.","Panjang ceritanya, dan membosankan.","Tergantung lu nanya siapa.","Sebuah benda. Benda yang penting banget.","Gua masih cari tau juga.")
POOL(ID_can, "Bisa. Mau? Itu pertanyaan lain.","Bisa. Nanti.","Mungkin. Jangan kutip gua.","Nggak. Bukan hari ini.","Gua bisa segalanya, kecuali terbang dan matematika.","Bisa. Apa untungnya buat gua?","Tergantung. Bahaya nggak?","Mau banget, tapi jadwal gua penuh kekosongan.")
POOL(ID_do, "Iya, kurang lebih.","Enggak sih, nggak juga.","Kadang. Tergantung harinya.","Jujur? Iya. Dan enggak.","Iya. Aneh ya?","Kenapa lu pengen tau?","Dulu iya. Sekarang enggak.","Banget. Jangan tanya kenapa.")
POOL(ES_why, "Porque así es.","¿Por qué no?","Nadie lo sabe.","Porque la vida es rara.")
POOL(ES_how, "Con cuidado, mucho cuidado.","Con suerte y cinta adhesiva.","Poco a poco.")
POOL(ES_when, "Cuando estés listo.","Pronto. O tarde.","Ahora, o en una hora.")
POOL(ES_who, "Nadie importante.","Un tipo. Olvidé su nombre.","Quién sabe.")
POOL(ES_what, "Buena pregunta. ¿Tú qué crees?","Ni idea, hermano.","Algo raro. Quizás un sándwich.")
POOL(ES_can, "Podría. ¿Lo haré? Otra pregunta.","Quizás.","Hoy no, amigo.")
POOL(ES_do, "Sí, más o menos.","No, la verdad que no.","A veces.")
POOL(EN_echo, "{w}? Hmm, not sure what to say about {w}.","You really wanna talk about {w}? Okay, go on.","Interesting. What's the deal with {w}?","I don't know much about {w}, to be honest.","{w}... that reminds me of something. Never mind.","Why bring up {w}?","Nobody around here ever mentions {w}. Until you.","Funny, I was just thinking about {w}. Okay, no I wasn't.","What about {w}?","{w} is a big topic. I'm a small guy.","Huh. {w}. Never thought about it.","So... {w}. Okay. Tell me more.","I have mixed feelings about {w}. Mostly confusion.","Let me guess: you're a {w} person.")
POOL(ID_echo, "{w}? Hmm, gua nggak yakin mau bilang apa soal {w}.","Lu beneran mau ngomongin {w}? Oke, lanjut.","Menarik. Ada apa sama {w}?","Gua nggak banyak tau soal {w}, jujur.","Kenapa tiba-tiba bahas {w}?","{w} ya... jadi inget sesuatu. Nggak jadi.","Soal {w}, gua netral aja.","Wah, {w}. Topik berat nih.","Baru kali ini ada yang bahas {w} sama gua.","{w}... gua belum pernah mikirin itu.","Terus, {w} kenapa?","Hmm, {w}. Oke, gua dengerin.","Gua punya perasaan campur aduk soal {w}.","Gua tebak: lu orang {w}.")
POOL(ES_echo, "¿{w}? Mmm, no sé qué decir sobre {w}.","¿De verdad quieres hablar de {w}? Adelante.","Interesante. ¿Qué pasa con {w}?","No sé mucho de {w}, la verdad.","¿Por qué sacas el tema de {w}?")
POOL(STOP_EN, "the","and","you","your","are","was","were","this","that","with","have","has","had","for","not","but","can","could","would","will","just","very","really","about","what","why","how","when","where","who","which","like","love","hate","think","know","want","need","tell","say","said","get","got","going","there","here","than","then","also","please","hey","hello","dude","bro","man","some","any","all","its","dont","does","did","from","they","them","our","out","off","too","yes","yeah","okay","gonna","wanna","lets","think","thoughts","opinion","feel","feeling","about","menurut","soal","tentang","pendapat","gimana")
POOL(STOP_ID, "yang","dan","atau","ini","itu","apa","siapa","kenapa","gimana","bagaimana","kapan","dimana","untuk","sama","juga","lagi","udah","sudah","belum","mau","bisa","boleh","jangan","tolong","aku","gua","gue","saya","kamu","kau","dia","kita","kami","mereka","nih","dong","sih","deh","kok","aja","banget","nggak","enggak","tidak","bukan","ada","punya","suka","benci","kalau","kalo","karena","tapi","tetapi","iya","oke","halo","hai","bro","bang","emang","pernah","lebih","dari","dengan","pada","akan","ke","di","buat")
POOL(STOP_ES, "que","qué","como","cómo","para","pero","porque","donde","dónde","cuando","quien","quién","tengo","quiero","estoy","eres","tienes","puedes","mucho","muy","también","amigo","hola","gracias","por","con","los","las","una","uno","del","esto","eso","aqui","aquí")

// ===================== GANG: pool dengan token {g}=nama geng {c}=warna {rv}=musuh {p}=nama player =====================
POOL(GW_greet, "{p}! Look who's back on {g} turf!","Ayy, {p}! What's good?","Yo {p}, you good? Welcome home.","{p}, my guy! {g} stays winning.","Well damn, it's {p}. Come here!","Welcome back, {p}. Everybody's been asking about you.","{c} love, {p}. You know it.","There he is! {p}! How's the family?","Ayy, {p}, you're one of us. Always.","{p}, glad you're breathing. Stay close.","Look at this! {p} in the building!","Hey, family. You hungry? We got food.","{g} for life, {p}!","Don't be a stranger, {p}. This is your home.","Aye, {p}! Hands up if you missed me.","{p}! You're good with me, always.")
POOL(GW_howare, "Livin' good now that you're here, {p}.","Strong, strong. {g} holding it down.","Can't complain, {p}. Not on my turf.","Better than the {rv}, that's for sure.","Chillin', blessed, repping {g}.","All good, fam. You?","Fine now. Better now that you showed.","Keeping it {c}, {p}.")
POOL(GW_bye, "Stay safe, {p}. {g} got your back.","Watch your six out there.","Come back soon, {p}.","Peace, family.","Go get 'em, {p}.","Don't let the {rv} catch you slipping.","{g} for life, {p}.","Catch you on the flip, fam.")
POOL(GW_name, "I'm {n}. {g} all day, {p}.","{n}. You know me, {p}. Everyone does.","They call me {n}. I roll with {g}.","{n}, {g} soldier. At your service.","It's {n}, fam. Don't forget it.","{n}. Keep it {c}.")
POOL(GW_thanks, "Anything for family, {p}.","Ain't nothing, {p}.","We look out for each other.","That's what {g} does.","No thanks needed, fam.")
POOL(GW_default, "You know how it is, {p}.","Stay {c}, {p}.","Preach, {p}, preach.","That's real talk right there.","Fam, I hear you.","{g} on top, always.","Straight up.","For real, for real.","Ain't that the truth.","Keep your head up, {p}.","Watch out for the {rv}, they're lurking.","We all eat when we stick together.","Say less, fam.","I got you, {p}.")
POOL(GH_greet, "You lost, {p}? This is {g} turf.","What you doing around here, fool?","Wrong side of town, {p}.","Ay, you got some nerve showing up here.","Hmph. {p}. Keep walking.","This ain't your block, scrub.","You want trouble? Because this is how you get trouble.","Eyes forward, {p}. And keep 'em off me.","We don't do friendly with your kind.","Better have a reason to be here.","Look what the {rv} dragged in.","You in {c} territory now, fool.","Don't stare, busta.","What you want, outsider?")
POOL(GH_howare, "Better than you, fool.","None of your business, {p}.","I'm fine. You should worry about yourself.","Great, until you showed up.","Ask me when you're not on my turf.","Why you wanna know, scrub?")
POOL(GH_bye, "Yeah, keep walking.","Get off my block.","Don't come back, {p}.","Next time, you won't walk away.","Bye, fool. Don't turn around.","Disappear.","We're done here.","See you in the wrong place, {p}.")
POOL(GH_name, "I'm {n}, and you better remember it.","{n}. {g}. That's all you need.","Why you asking? I'm {n}. Now go.","The name's {n}. Don't forget who runs this.","{n}. Move along, {p}.","None of your business. {n}. There.")
POOL(GH_thanks, "Don't mention it. Ever.","Whatever. Go.","I didn't do it for you.","Yeah, yeah, don't make it weird.","Save it, {p}.")
POOL(GH_default, "I ain't got time for you.","Talk to somebody who cares.","You're pushing it, {p}.","{rv} loves hanging with you? Figures.","Mm-hmm. Keep talking, see what happens.","Stay out of {g} business.","You think you're special? You ain't.","Say what you came to say and go.","Man, whatever.","Don't test me, scrub.","I'm not scared of you, {p}.","Do yourself a favor, leave.","Boring. Next.","You done?")
POOL(GH_insult, "Look at this clown.","Bet you can't even fight, {p}.","You smell like {rv} cologne.","Scrub. Total scrub.","Walk like that and you'll get lost, fool.","Nice outfit. Ask your mama to dress you?","You a joke, {p}.","Where's your crew? Oh, right, nowhere.","Trash. Pure trash.","Keep dreaming, busta.","Man, you're a walking mistake.","Get outta my face, {p}.")
POOL(GC_greet, "Yes? Can I help you?","State your business.","Hm. What do you need?","Keep it polite and we'll get along.","You're not from around here.","I'm listening. Briefly.","Do I know you?","Make it quick.","Speak. Respectfully.","Don't waste my time.")
POOL(GC_default, "I see.","Understood.","That is none of my concern.","Interesting. Continue.","We handle our own business.","Let's keep it simple.","I don't discuss that.","Respect goes both ways.","Mind your manners and we're fine.","Noted.")
POOL(GC_bye, "Goodbye.","Safe travels.","Don't make me regret this chat.","Until next time.","Move along.","Have a good day.")
POOL(GC_name, "I'm {n}. That is enough.","{n}. And you?","They call me {n}.","{n}. Pleased, I suppose.","Names are for friends. {n}, though.")
POOL(GANGTALK, "{g}? That's family. {rv}? That's trouble.","I rep {g}, always have, always will.","Colors matter. I wear {c} for a reason.","The {rv} think they run things. They don't.","Gang life ain't a game, {p}.","I joined {g} because they had my back.","Respect the colors, respect yourself.","{g} stays strong, no matter what.","Turf wars are tiring, but somebody's gotta do it.","You don't mess with {g}. Simple as that.")
POOL(ID_GW_greet, "{p}! Akhirnya balik juga ke wilayah {g}!","Wih, {p}! Apa kabar, keluarga?","{p}, selamat datang di rumah!","Yo {p}! {g} selalu di hati!","Lu udah gua anggap saudara, {p}.","Gimana, {p}? Aman?")
POOL(ID_GH_greet, "Lu nyasar, {p}? Ini wilayah {g}.","Ngapain lu di sini, culun?","Salah tempat, {p}.","Jangan liatin gua, busta.","Berani juga lu muncul di sini.","Minggir sebelum gua marah.")
POOL(ES_GW_greet, "¡{p}! ¡Qué bueno verte, hermano!","Bienvenido a casa, {p}.","¡{g} para siempre!","¡Ey, {p}! ¿Todo bien, familia?")
POOL(ES_GH_greet, "¿Qué haces aquí, {p}? Esta es zona de {g}.","Largo de aquí, ese.","No eres bienvenido.","Cuidado con lo que haces, {p}.")
POOL(TAG_GSF, "cuz","homie","fam","G")
POOL(TAG_BALLAS, "fool","busta","scrub")
POOL(TAG_VAGOS, "ese","vato","homes","carnal")
POOL(TAG_AZTECAS, "carnal","esa","mijo","vato")
POOL(TAG_ASIAN, "friend")
POOL(TAG_MAFIA, "paisan","pal","kid")
POOL(TAG_RIFA, "compa","hermano","homie")
POOL(TAG_BIKER, "dude","brother","buddy")

} // namespace VocabData

// ======================================================================
//  MESIN KOSAKATA: deteksi topik, pilih balasan, generator kalimat acak
// ======================================================================
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <initializer_list>

namespace Vocab {
using namespace VocabData;

struct Pool { const char* const* d; size_t n; };
#define PL(X) Pool{X, sizeof(X) / sizeof(X[0])}
static const Pool NOPOOL = {nullptr, 0};

enum Cat { C_GREET, C_HOWARE, C_NAME, C_THANKS, C_BYE, C_SORRY, C_YES, C_NO, C_MONEY, C_DIRECTIONS, C_LOVE, C_COMPLIMENT,
           C_INSULT, C_THREAT, C_JOKE, C_WEATHER, C_FOOD, C_MUSIC, C_CARS, C_POLICE, C_GANG, C_WORK, C_FAMILY, C_AGE, C_FROM,
           C_TIME, C_HELP, C_SLEEP, C_GAMES, C_LIKE, C_STORY, C_WHY, C_HOW, C_WHEN, C_WHO, C_WHAT, C_CAN, C_DO, C_QUESTION, C_DEFAULT, C_COUNT };

// v (mood): 0 netral, 1 marah, 2 takut, 3 senang.  Untuk INSULT/THREAT: 0 penakut, 1 galak, 2 netral.
inline Pool PoolEN(int c, int v) {
    switch (c) {
        case C_GREET:   return v == 1 ? PL(EN_greet_angry) : v == 2 ? PL(EN_greet_scared) : v == 3 ? PL(EN_greet_happy) : PL(EN_greet);
        case C_HOWARE:  return v == 1 ? PL(EN_howare_angry) : v == 2 ? PL(EN_howare_scared) : v == 3 ? PL(EN_howare_happy) : PL(EN_howare);
        case C_NAME: return PL(EN_name);       case C_THANKS: return PL(EN_thanks);   case C_BYE: return PL(EN_bye);
        case C_SORRY: return PL(EN_sorry);     case C_YES: return PL(EN_yes);         case C_NO: return PL(EN_no);
        case C_MONEY: return PL(EN_money);     case C_DIRECTIONS: return PL(EN_directions); case C_LOVE: return PL(EN_love);
        case C_COMPLIMENT: return PL(EN_compliment);
        case C_INSULT:  return v == 0 ? PL(EN_insult_nervous) : v == 1 ? PL(EN_insult_tough) : PL(EN_insult_neutral);
        case C_THREAT:  return v == 0 ? PL(EN_threat_scared) : v == 1 ? PL(EN_threat_tough) : PL(EN_threat_neutral);
        case C_JOKE: return PL(EN_joke);       case C_WEATHER: return PL(EN_weather); case C_FOOD: return PL(EN_food);
        case C_MUSIC: return PL(EN_music);     case C_CARS: return PL(EN_cars);       case C_POLICE: return PL(EN_police);
        case C_GANG: return PL(EN_gang);       case C_WORK: return PL(EN_work);       case C_FAMILY: return PL(EN_family);
        case C_AGE: return PL(EN_age);         case C_FROM: return PL(EN_from);       case C_TIME: return PL(EN_time);
        case C_HELP: return PL(EN_help);       case C_SLEEP: return PL(EN_sleep);     case C_GAMES: return PL(EN_games);
        case C_LIKE: return PL(EN_like);   case C_WHY: return PL(EN_why);   case C_HOW: return PL(EN_how);
        case C_WHEN: return PL(EN_when);   case C_WHO: return PL(EN_who);   case C_WHAT: return PL(EN_what);
        case C_CAN: return PL(EN_can);     case C_DO: return PL(EN_do);     case C_STORY: return NOPOOL;
        case C_QUESTION: return PL(EN_question);
        default: return v == 1 ? PL(EN_default_angry) : v == 2 ? PL(EN_default_scared) : v == 3 ? PL(EN_default_happy) : PL(EN_default);
    }
}
inline Pool PoolID(int c, int v) {
    switch (c) {
        case C_GREET:   return v == 1 ? PL(ID_greet_angry) : v == 2 ? PL(ID_greet_scared) : v == 3 ? PL(ID_greet_happy) : PL(ID_greet);
        case C_HOWARE:  return v == 1 ? PL(ID_howare_angry) : v == 2 ? PL(ID_howare_scared) : v == 3 ? PL(ID_howare_happy) : PL(ID_howare);
        case C_NAME: return PL(ID_name);       case C_THANKS: return PL(ID_thanks);   case C_BYE: return PL(ID_bye);
        case C_SORRY: return PL(ID_sorry);     case C_YES: return PL(ID_yes);         case C_NO: return PL(ID_no);
        case C_MONEY: return PL(ID_money);     case C_DIRECTIONS: return PL(ID_directions); case C_LOVE: return PL(ID_love);
        case C_COMPLIMENT: return PL(ID_compliment); case C_INSULT: return PL(ID_insult); case C_THREAT: return PL(ID_threat);
        case C_JOKE: return PL(ID_joke);       case C_WEATHER: return PL(ID_weather); case C_FOOD: return PL(ID_food);
        case C_MUSIC: return PL(ID_music);     case C_CARS: return PL(ID_cars);       case C_POLICE: return PL(ID_police);
        case C_GANG: return PL(ID_gang);       case C_WORK: return PL(ID_work);       case C_FAMILY: return PL(ID_family);
        case C_AGE: return PL(ID_age);         case C_FROM: return PL(ID_from);       case C_TIME: return PL(ID_time);
        case C_HELP: return PL(ID_help);       case C_SLEEP: return PL(ID_sleep);     case C_GAMES: return PL(ID_games);
        case C_LIKE: return PL(ID_like);   case C_WHY: return PL(ID_why);   case C_HOW: return PL(ID_how);
        case C_WHEN: return PL(ID_when);   case C_WHO: return PL(ID_who);   case C_WHAT: return PL(ID_what);
        case C_CAN: return PL(ID_can);     case C_DO: return PL(ID_do);     case C_STORY: return NOPOOL;
        case C_QUESTION: return PL(ID_question);
        default: return v == 1 ? PL(ID_default_angry) : v == 2 ? PL(ID_default_scared) : v == 3 ? PL(ID_default_happy) : PL(ID_default);
    }
}
inline Pool PoolES(int c, int v) {
    switch (c) {
        case C_GREET:   return v == 1 ? PL(ES_greet_angry) : v == 2 ? PL(ES_greet_scared) : v == 3 ? PL(ES_greet_happy) : PL(ES_greet);
        case C_HOWARE:  return v == 1 ? PL(ES_howare_angry) : v == 2 ? PL(ES_howare_scared) : v == 3 ? PL(ES_howare_happy) : PL(ES_howare);
        case C_NAME: return PL(ES_name);       case C_THANKS: return PL(ES_thanks);   case C_BYE: return PL(ES_bye);
        case C_SORRY: return PL(ES_sorry);     case C_YES: return PL(ES_yes);         case C_NO: return PL(ES_no);
        case C_MONEY: return PL(ES_money);     case C_DIRECTIONS: return PL(ES_directions); case C_LOVE: return PL(ES_love);
        case C_INSULT: return PL(ES_insult);   case C_THREAT: return PL(ES_threat);   case C_JOKE: return PL(ES_joke);
        case C_FOOD: return PL(ES_food);       case C_QUESTION: return PL(ES_question);
        case C_LIKE: return PL(ES_like);   case C_WHY: return PL(ES_why);   case C_HOW: return PL(ES_how);
        case C_WHEN: return PL(ES_when);   case C_WHO: return PL(ES_who);   case C_WHAT: return PL(ES_what);
        case C_CAN: return PL(ES_can);     case C_DO: return PL(ES_do);     case C_STORY: return NOPOOL;
        case C_COMPLIMENT: case C_WEATHER: case C_MUSIC: case C_CARS: case C_POLICE: case C_GANG: case C_WORK: case C_FAMILY:
        case C_AGE: case C_FROM: case C_TIME: case C_HELP: case C_SLEEP: case C_GAMES: return NOPOOL;   // jatuh ke ES_default
        default: return v == 1 ? PL(ES_default_angry) : v == 2 ? PL(ES_default_scared) : v == 3 ? PL(ES_default_happy) : PL(ES_default);
    }
}
inline Pool GetPool(int lang, int c, int v) {
    Pool p = lang == 1 ? PoolID(c, v) : lang == 2 ? PoolES(c, v) : PoolEN(c, v);
    if (p.n == 0) p = lang == 1 ? PoolID(C_DEFAULT, v) : lang == 2 ? PoolES(C_DEFAULT, v) : PoolEN(C_DEFAULT, v);
    return p;
}
inline Pool FeelPool(int lang, int k) {                               // 0 sedih 1 capek 2 senang 3 marah 4 takut 5 bosen 6 sakit
    switch (k) {
        case 0: return lang == 1 ? PL(ID_feel_sad)   : lang == 2 ? PL(ES_feel_sad)   : PL(EN_feel_sad);
        case 1: return lang == 1 ? PL(ID_feel_tired) : lang == 2 ? PL(ES_feel_tired) : PL(EN_feel_tired);
        case 2: return lang == 1 ? PL(ID_feel_happy) : lang == 2 ? PL(ES_feel_happy) : PL(EN_feel_happy);
        case 3: return lang == 1 ? PL(ID_feel_angry) : lang == 2 ? PL(ES_feel_angry) : PL(EN_feel_angry);
        case 4: return lang == 1 ? PL(ID_feel_scared): lang == 2 ? PL(ES_feel_scared): PL(EN_feel_scared);
        case 5: return lang == 1 ? PL(ID_feel_bored) : lang == 2 ? PL(ES_feel_bored) : PL(EN_feel_bored);
        default: return lang == 1 ? PL(ID_feel_sick) : lang == 2 ? PL(ES_feel_sick)  : PL(EN_feel_sick);
    }
}
inline Pool PoolEcho(int lang) { return lang == 1 ? PL(ID_echo) : lang == 2 ? PL(ES_echo) : PL(EN_echo); }
inline Pool PoolRandom(int lang) { return lang == 1 ? PL(ID_random) : lang == 2 ? PL(ES_random) : PL(EN_random); }
inline Pool PoolAbsurd(int lang) { return lang == 1 ? PL(ID_absurd) : lang == 2 ? PL(ES_absurd) : PL(EN_absurd); }
inline Pool PoolMumble(int lang) { return lang == 1 ? PL(ID_mumble) : lang == 2 ? PL(ES_mumble) : PL(EN_mumble); }
inline Pool PoolSpGreet(int lang) { return lang == 1 ? PL(ID_sp_greet) : lang == 2 ? PL(ES_sp_greet) : PL(EN_sp_greet); }
inline Pool PoolSpInsult(int lang) { return lang == 1 ? PL(ID_sp_insult) : lang == 2 ? PL(ES_sp_insult) : PL(EN_sp_insult); }

// ---------- deteksi topik (kata kunci gabungan 3 bahasa; spasi = batas kata) ----------
// Normalisasi: huruf kecil, apostrof dihapus, tanda baca jadi spasi, diapit spasi. ("Cars?" -> " cars ")
inline std::string NormText(const std::string& s) {
    std::string t = " "; bool lastSpace = true;
    for (unsigned char c : s) {
        if (c == '\'') continue;
        char o = c >= 128 ? (char)c : (isalnum(c) ? (char)tolower(c) : ' ');
        if (o == ' ') { if (!lastSpace) t += ' '; lastSpace = true; }
        else { t += o; lastSpace = false; }
    }
    if (!lastSpace) t += ' ';
    return t;
}
inline std::string LowerPad(const std::string& s) { return NormText(s); }
inline std::string NormKw(const char* k) {                           // kata kunci dinormalkan; spasi awal/akhir yang disengaja dipertahankan
    std::string in = k; bool lead = !in.empty() && in.front() == ' ', trail = in.size() > 1 && in.back() == ' ';
    std::string n = NormText(in);
    if (!lead && n.size() > 1) n.erase(0, 1);
    if (!trail && n.size() > 1) n.pop_back();
    return n;
}
inline bool HasAnyN(const std::string& t, std::initializer_list<const char*> ks) {
    for (auto k : ks) if (t.find(NormKw(k)) != std::string::npos) return true;
    return false;
}
#define KW(NAME, ...) static const char* const NAME[] = { __VA_ARGS__ };
KW(K_THREAT, "kill you","shoot you","i'll kill","gonna kill","beat you","hurt you","you're dead","you are dead","bury you","stab you","bunuh","tembak","mati lu","hajar","habisi","pukul gua","te voy a matar","te mato")
KW(K_INSULT, "idiot","stupid"," dumb","asshole","bitch","fuck you","loser","ugly","shut up","moron","jerk","bastard","freak","trash","goblok","bodoh","tolol","anjing","bangsat","sialan","brengsek","kampret","jelek","pecundang","idiota","estúpido","imbécil","cállate","pendejo")
KW(K_SORRY, "sorry","apologize","my bad","forgive me","maaf"," sori ","perdón","perdon","lo siento")
KW(K_THANKS, "thank","thx","appreciate","makasih","terima kasih","tengkyu","gracias")
KW(K_BYE, "bye","goodbye","see you","see ya","gotta go","i'm leaving","take care"," later ","dadah","sampai jumpa","duluan","cabut","adiós","adios","hasta luego","nos vemos")
KW(K_NAME, "your name","who are you","introduce yourself","nama lu","nama lo","nama kamu","namamu","nama anda","kamu siapa","lu siapa","lo siapa","elu siapa","siapa lu","siapa lo","siapa kamu","siapa nama","siapa anda","tu nombre","cómo te llamas","como te llamas","quién eres","quien eres")
KW(K_HOWARE, "how are you","how's it going","hows it going","how you doing","how are things","how do you do","what's up","whats up","apa kabar","gimana kabar","kabar lu","lagi apa","cómo estás","como estas","qué tal","que tal")
KW(K_GREET, "hello"," hi ","hey"," yo ","sup ","howdy","good morning","good evening","good afternoon","greetings","halo"," hai ","woi","woy","pagi","siang"," sore ","malam","assalamualaikum","salam","hola","buenos","buenas","oye","wassup"," test "," tes ")
KW(K_JOKE, "joke","funny","make me laugh"," lol ","haha","lucu","bercanda","ketawa","chiste","broma","gracioso")
KW(K_LOVE, "love you","beautiful","handsome"," pretty ","sexy"," cute ","date me","girlfriend","boyfriend","marry me","cinta","sayang","cantik","ganteng","pacar","jodoh","te amo","guapo","guapa","novia","novio")
KW(K_COMPLIMENT, " nice "," cool ","awesome","amazing","good job","love your","like your","keren","bagus","mantap","hebat","genial","increíble","buen trabajo"," great ")
KW(K_MONEY, "money","cash","dollar"," buck","lend","borrow","loan"," broke ","rich","poor"," pay ","uang","duit","pinjam","minjem","bayar"," kaya ","miskin","dinero","plata","prestame")
KW(K_DIRECTIONS, "where is","where's","how do i get","directions","which way"," lost ","hospital","police station"," gym ","store","shop","restaurant","airport","dimana","di mana"," arah ","jalan ke","nyasar"," toko ","rumah sakit","dónde","donde está","como llego")
KW(K_POLICE, " cop "," cops ","police","sheriff","arrest"," jail ","prison"," fbi ","swat","polisi","penjara","tangkap","policía","cárcel")
KW(K_GANG, " gang","grove","ballas","vagos","aztecas"," hood "," turf "," crew ","homies"," geng ","wilayah","pandilla","barrio")
KW(K_FOOD, " food ","hungry"," eat ","pizza","burger","taco","hot dog","chicken","dinner","lunch","breakfast","coffee"," beer ","drink","thirsty","makan","lapar","minum","kopi"," bir ","comida","hambre","comer","cerveza")
KW(K_MUSIC, "music"," song "," rap ","hip hop"," rock ","radio"," sing ","concert"," band ","musik"," lagu ","nyanyi","música","canción","cantar")
KW(K_CARS, " car "," cars ","truck"," bike ","motorcycle"," drive ","lowrider","engine","speed"," race ","mobil"," motor ","balap","coche","carro"," moto ")
KW(K_WEATHER, "weather"," rain","sunny"," hot "," cold ","storm","snow","hujan","panas","dingin","cuaca","clima","lluvia","calor","frío")
KW(K_WORK, " job "," work ","boss","salary","career","business","unemployed","kerja","pekerjaan"," bos ","gaji","trabajo","jefe","empleo")
KW(K_FAMILY, "family","mother"," mom "," dad ","father","sister","brother"," kids "," wife ","husband","keluarga"," ibu ","ayah"," adik ","kakak","istri","suami","familia","madre","padre","hermano","hermana")
KW(K_AGE, "how old","your age","umur","usia","berapa tahun","cuántos años","edad")
KW(K_FROM, "where are you from","where you from","hometown","asal lu","dari mana","lahir","de dónde","de donde")
KW(K_TIME, "what time","time is it","jam berapa","sekarang jam","qué hora","que hora")
KW(K_HELP, " help ","need help","assist","emergency","tolong","bantu","ayuda","socorro")
KW(K_SLEEP, "sleep","tired","sleepy"," nap "," bed ","tidur","capek","ngantuk","dormir","cansado")
KW(K_GAMES, " game"," gta ","video game","console"," play ","main game","juego","jugar")
KW(K_YES, " yes "," yeah "," yep "," sure ","of course","definitely"," iya "," betul ","benar"," sí "," claro ")
KW(K_NO, " no "," nope "," nah "," never ","not really","tidak","nggak"," gak ","enggak"," jangan ")

KW(K_LIKE, "do you like","do you love","do you hate","you like ","what do you think about","what do you think of","how do you feel about","are you a fan","kamu suka","lu suka","lo suka","kau suka","menurut lu","menurut kamu","menurut lo","pendapat lu","pendapat kamu","suka nggak","suka ga","te gusta","te gustan","qué piensas de","que piensas de")
KW(K_STORY, "tell me a story","tell me about yourself","tell me something","tell me more","story","cerita","ceritain","ceritakan","dongeng","cuéntame","cuentame","historia")
KW(K_QCAN, " can you "," could you "," would you "," will you ","bisakah","bisa ga","bisa nggak","bisa gak"," bisa ","puedes","podrías","podrias")
KW(K_QDO, " do you "," are you "," did you "," have you "," is it ","apakah"," apa lu "," apa kamu "," emang "," tu eres ")
KW(K_QWHY, " why ","kenapa","mengapa","por que","por qué")
KW(K_QHOW, " how ","bagaimana","gimana","caranya"," cómo "," como ")
KW(K_QWHEN, " when ","kapan","cuando","cuándo")
KW(K_QWHO, " who ","siapa","quién","quien")
KW(K_QWHAT, " what "," apa ","apaan"," qué "," que ")
KW(K_FP, " i am "," im "," i feel "," ive been "," gua "," gue "," gw "," aku "," saya "," estoy "," me siento "," lagi ")
KW(K_F_SAD, "sad","depress","cry","lonely","heartbroken","miserable","sedih","nangis","galau","patah hati","triste","llorar")
KW(K_F_TIRED, "tired","exhausted","sleepy","worn out","capek","lelah","ngantuk"," cape ","cansad")
KW(K_F_HAPPY, "happy","excited","great day"," glad ","senang","seneng","bahagia","gembira","feliz","contento")
KW(K_F_ANGRY, "angry"," mad ","pissed","furious","annoyed","marah","kesel","kesal","emosi","enojad","molest")
KW(K_F_SCARED, "scared","afraid","terrified","nervous","anxious","takut","ngeri","cemas","miedo","asustad")
KW(K_F_BORED, "bored","boring","bosen","bosan","aburrid")
KW(K_F_SICK, " sick "," ill ","headache","fever","sakit","pusing","demam","enferm")

struct KwEntry { int cat; std::vector<std::string> k; };
inline KwEntry MakeKE(int c, const char* const* d, size_t n) { KwEntry e; e.cat = c; for (size_t i = 0; i < n; i++) e.k.push_back(NormKw(d[i])); return e; }
#define KE(C, K) MakeKE(C, K, sizeof(K) / sizeof(K[0]))
inline const std::vector<KwEntry>& KwTable() {                      // urutan = prioritas
    static const std::vector<KwEntry> t = {
        KE(C_THREAT, K_THREAT), KE(C_INSULT, K_INSULT), KE(C_SORRY, K_SORRY), KE(C_THANKS, K_THANKS), KE(C_BYE, K_BYE),
        KE(C_NAME, K_NAME), KE(C_HOWARE, K_HOWARE), KE(C_LIKE, K_LIKE), KE(C_JOKE, K_JOKE), KE(C_STORY, K_STORY), KE(C_LOVE, K_LOVE), KE(C_COMPLIMENT, K_COMPLIMENT),
        KE(C_MONEY, K_MONEY), KE(C_DIRECTIONS, K_DIRECTIONS), KE(C_POLICE, K_POLICE), KE(C_GANG, K_GANG), KE(C_FOOD, K_FOOD),
        KE(C_MUSIC, K_MUSIC), KE(C_CARS, K_CARS), KE(C_WEATHER, K_WEATHER), KE(C_WORK, K_WORK), KE(C_FAMILY, K_FAMILY),
        KE(C_AGE, K_AGE), KE(C_FROM, K_FROM), KE(C_TIME, K_TIME), KE(C_HELP, K_HELP), KE(C_SLEEP, K_SLEEP), KE(C_GAMES, K_GAMES),
        KE(C_YES, K_YES), KE(C_NO, K_NO), KE(C_GREET, K_GREET) };
    return t;
}
inline const std::vector<KwEntry>& KwQuestions() {                  // dipakai bila tidak ada topik lain
    static const std::vector<KwEntry> t = { KE(C_CAN, K_QCAN), KE(C_DO, K_QDO), KE(C_WHY, K_QWHY), KE(C_HOW, K_QHOW), KE(C_WHEN, K_QWHEN), KE(C_WHO, K_QWHO), KE(C_WHAT, K_QWHAT) };
    return t;
}
inline bool MatchAny(const std::string& t, const KwEntry& e) { for (auto& k : e.k) if (t.find(k) != std::string::npos) return true; return false; }
inline std::vector<int> DetectAll(const std::string& padded) {
    std::vector<int> out;
    for (auto& e : KwTable()) if (MatchAny(padded, e)) out.push_back(e.cat);
    return out;
}
inline int DetectQuestionType(const std::string& padded) {
    for (auto& e : KwQuestions()) if (MatchAny(padded, e)) return e.cat;
    return -1;
}
inline int DetectFeel(const std::string& padded) {                  // perlu penanda orang pertama ("gua lagi sedih", "i am tired")
    static const KwEntry fp = MakeKE(0, K_FP, sizeof(K_FP) / sizeof(K_FP[0]));
    if (!MatchAny(padded, fp)) return -1;
    static const KwEntry f[7] = { MakeKE(0, K_F_SAD, sizeof(K_F_SAD) / sizeof(K_F_SAD[0])), MakeKE(1, K_F_TIRED, sizeof(K_F_TIRED) / sizeof(K_F_TIRED[0])),
        MakeKE(2, K_F_HAPPY, sizeof(K_F_HAPPY) / sizeof(K_F_HAPPY[0])), MakeKE(3, K_F_ANGRY, sizeof(K_F_ANGRY) / sizeof(K_F_ANGRY[0])),
        MakeKE(4, K_F_SCARED, sizeof(K_F_SCARED) / sizeof(K_F_SCARED[0])), MakeKE(5, K_F_BORED, sizeof(K_F_BORED) / sizeof(K_F_BORED[0])),
        MakeKE(6, K_F_SICK, sizeof(K_F_SICK) / sizeof(K_F_SICK[0])) };
    for (int i = 0; i < 7; i++) if (MatchAny(padded, f[i])) return i;
    return -1;
}
// Kata kunci dari ucapan player (kata terpanjang yang bukan kata umum) untuk "menggemakan" topiknya
inline std::string Keyword(const std::string& padded) {
    std::vector<std::string> tok; std::string cur;
    for (char ch : padded) { if (ch == ' ') { if (!cur.empty()) tok.push_back(cur); cur.clear(); } else cur += ch; }
    std::string best;
    for (auto& w : tok) {
        if (w.size() < 3) continue;
        bool stop = false;
        for (size_t i = 0; i < sizeof(STOP_EN) / sizeof(STOP_EN[0]) && !stop; i++) if (w == STOP_EN[i]) stop = true;
        for (size_t i = 0; i < sizeof(STOP_ID) / sizeof(STOP_ID[0]) && !stop; i++) if (w == STOP_ID[i]) stop = true;
        for (size_t i = 0; i < sizeof(STOP_ES) / sizeof(STOP_ES[0]) && !stop; i++) if (w == STOP_ES[i]) stop = true;
        if (stop) continue;
        if (w.size() >= best.size()) best = w;
    }
    return best;
}

// ---------- generator kalimat acak (kombinasi ribuan) ----------
POOL(G_EN_open, "Well,","Look,","Honestly,","Man,","Listen,","Okay so,","You know what?","Hold on,","Funny thing,","Real talk:","Not to brag, but","Fun fact:","Between you and me,","Don't tell anyone, but","Back in the day,","True story:","No joke,","Weirdly enough,","Just so you know,","So yesterday,")
POOL(G_EN_did, "ate","fought","married","adopted","outran","argued with","hid from","painted","sold","borrowed","lost","found","befriended","interviewed","apologized to","chased","raced","fed","named","baked")
POOL(G_EN_obj, "a goat","three pigeons","a very angry mailman","my own shadow","a vending machine","a possum in a tuxedo","a talking parrot","my neighbor's lawn gnome","a haunted toaster","a two-headed squirrel","a mime","a lost tourist","a man named Gary","a shopping cart","an entire pizza","a suspicious raccoon","a dancing cactus","a runaway clown","a very polite crow","my third cousin")
POOL(G_EN_place, "behind a gas station","at 3 AM","in a parking lot","during a thunderstorm","on a Tuesday","at my cousin's wedding","in the middle of traffic","outside a taco truck","under a bridge","at the beach","on a rooftop","in a laundromat","at the DMV","at a funeral","inside an elevator","near the airport","at a barbecue","in a library","on a bus","right here")
POOL(G_EN_tail, "Anyway.","Long story.","Don't ask.","True story.","I stand by it.","Worth it.","Never again.","Would do it again.","Still thinking about it.","Ask me about it later.","Changed my life.","Don't tell my mom.","That's all I'll say.","Moving on.","It's a whole thing.")
POOL(G_EN_rel, "uncle","cousin","landlord","barber","neighbor","grandma","dentist","dog","hairdresser","boss","mailman","bartender")
POOL(G_EN_claim, "the moon is just a big nightlight","pigeons run the economy","socks are time travelers","tacos cure everything","Tuesdays are a scam","all clouds are tired","the sidewalk is alive","traffic lights have feelings","every car is secretly a horse","ketchup is a vegetable","the ocean is just a really big puddle","birds aren't real, but sandwiches are","shoes gossip when you're asleep","the DMV is a portal","every mailbox is watching")
POOL(G_ID_open, "Jadi gini,","Serius,","Asli,","Eh dengerin,","Jujur aja,","Cerita dikit ya,","Kemarin tuh,","Gua kasih tau ya,")
POOL(G_ID_did, "makan","berantem sama","nikahin","adopsi","ngejar","debat sama","sembunyi dari","jual","pinjem","nemuin")
POOL(G_ID_obj, "kambing","tiga merpati","tukang pos yang lagi marah","bayangan gua sendiri","mesin minuman","landak pakai jas","burung beo yang bisa ngomong","kurcaci tetangga","pemanggang roti berhantu","badut kabur")
POOL(G_ID_place, "di belakang pom bensin","jam tiga pagi","di parkiran","pas hujan badai","hari Selasa","di nikahan sepupu","di tengah macet","di bawah jembatan","di pantai","di laundry")
POOL(G_ID_tail, "Ya gitu deh.","Panjang ceritanya.","Jangan nanya.","Serius ini.","Gua nggak nyesel.","Nggak lagi-lagi.")
POOL(G_ES_open, "Mira,","En serio,","Oye,","La verdad,","Te cuento,")
POOL(G_ES_did, "comí","peleé con","me casé con","adopté a","corrí tras","discutí con","me escondí de")
POOL(G_ES_obj, "una cabra","tres palomas","un cartero enojado","mi propia sombra","una máquina expendedora","un mapache sospechoso")
POOL(G_ES_place, "detrás de una gasolinera","a las tres de la mañana","en un estacionamiento","durante una tormenta","en la boda de mi primo","debajo de un puente")
POOL(G_ES_tail, "Larga historia.","No preguntes.","Verdad verdadera.","Lo volvería a hacer.")

inline const char* Pick(const Pool& p, std::mt19937& g) { return p.d[g() % p.n]; }
inline const char* PickA(const char* const* d, size_t n, std::mt19937& g) { return d[g() % n]; }
#define PICKP(X) Pick(PL(X), g)

inline std::string Compose(int lang, std::mt19937& g) {
    if (lang == 1) return std::string(PICKP(G_ID_open)) + " gua pernah " + PICKP(G_ID_did) + " " + PICKP(G_ID_obj) + " " + PICKP(G_ID_place) + ". " + PICKP(G_ID_tail);
    if (lang == 2) return std::string(PICKP(G_ES_open)) + " una vez " + PICKP(G_ES_did) + " " + PICKP(G_ES_obj) + " " + PICKP(G_ES_place) + ". " + PICKP(G_ES_tail);
    if (g() % 2) return std::string(PICKP(G_EN_open)) + " I once " + PICKP(G_EN_did) + " " + PICKP(G_EN_obj) + " " + PICKP(G_EN_place) + ". " + PICKP(G_EN_tail);
    return std::string("My ") + PICKP(G_EN_rel) + " says " + PICKP(G_EN_claim) + ". " + PICKP(G_EN_tail);
}


// ---------- geng & hubungan dengan player ----------
enum Gang { G_NONE = 0, G_GSF, G_BALLAS, G_VAGOS, G_AZTECAS, G_TRIAD, G_DANANG, G_MAFIA, G_RIFA, G_BIKER };
inline int GangOfSkin(int m) {                                         // dari ID skin GTA SA (perkiraan terbaik)
    switch (m) {
        case 105: case 106: case 107: case 269: case 270: case 271: return G_GSF;
        case 102: case 103: case 104: return G_BALLAS;
        case 108: case 109: case 110: return G_VAGOS;
        case 114: case 115: case 116: case 292: return G_AZTECAS;
        case 117: case 118: case 120: return G_TRIAD;
        case 121: case 122: case 123: return G_DANANG;
        case 111: case 112: case 113: case 124: case 125: case 126: case 127: return G_MAFIA;
        case 173: case 174: case 175: return G_RIFA;
        case 100: case 247: case 248: return G_BIKER;
        default: return G_NONE;
    }
}
inline const char* GangName(int g)  { static const char* n[] = {"", "Grove Street", "Ballas", "Vagos", "Aztecas", "Triad", "Da Nang", "Mafia", "Rifa", "bikers"}; return n[g < 0 || g > 9 ? 0 : g]; }
inline const char* GangColor(int g) { static const char* n[] = {"", "green", "purple", "yellow", "turquoise", "red", "jade", "black", "blue", "leather"}; return n[g < 0 || g > 9 ? 0 : g]; }
inline const char* GangRival(int g) { static const char* n[] = {"", "Ballas", "Grove Street", "Aztecas", "Vagos", "Da Nang", "Triad", "Triad", "Aztecas", "the cops"}; return n[g < 0 || g > 9 ? 0 : g]; }
// +2 satu geng/sekutu dekat, +1 sahabat, 0 netral, -1 saingan, -2 musuh bebuyutan
inline int Relation(int ped, int player) {
    if (ped == G_NONE) return 0;
    if (ped == player) return 2;
    auto is = [&](int a, int b) { return (ped == a && player == b) || (ped == b && player == a); };
    if (is(G_GSF, G_RIFA)) return 1;
    if (is(G_GSF, G_BALLAS) || is(G_VAGOS, G_AZTECAS) || is(G_TRIAD, G_DANANG)) return -2;
    if (is(G_GSF, G_VAGOS) || is(G_GSF, G_AZTECAS) || is(G_BALLAS, G_VAGOS) || is(G_BALLAS, G_AZTECAS) || is(G_MAFIA, G_TRIAD) || is(G_MAFIA, G_DANANG)) return -1;
    return 0;
}
inline Pool GangTags(int g) {
    switch (g) { case G_GSF: return PL(TAG_GSF); case G_BALLAS: return PL(TAG_BALLAS); case G_VAGOS: return PL(TAG_VAGOS);
                 case G_AZTECAS: return PL(TAG_AZTECAS); case G_TRIAD: case G_DANANG: return PL(TAG_ASIAN); case G_MAFIA: return PL(TAG_MAFIA);
                 case G_RIFA: return PL(TAG_RIFA); case G_BIKER: return PL(TAG_BIKER); default: return NOPOOL; }
}
// kind: 0 sambutan hangat, 1 permusuhan, 2 dingin/formal
inline Pool GangPool(int cat, int kind, int lang) {
    if (lang == 1 && cat == C_GREET) return kind == 0 ? PL(ID_GW_greet) : kind == 1 ? PL(ID_GH_greet) : NOPOOL;
    if (lang == 2 && cat == C_GREET) return kind == 0 ? PL(ES_GW_greet) : kind == 1 ? PL(ES_GH_greet) : NOPOOL;
    if (lang != 0) return NOPOOL;
    switch (cat) {
        case C_GREET:  return kind == 0 ? PL(GW_greet)  : kind == 1 ? PL(GH_greet)  : PL(GC_greet);
        case C_HOWARE: return kind == 0 ? PL(GW_howare) : kind == 1 ? PL(GH_howare) : NOPOOL;
        case C_BYE:    return kind == 0 ? PL(GW_bye)    : kind == 1 ? PL(GH_bye)    : PL(GC_bye);
        case C_NAME:   return kind == 0 ? PL(GW_name)   : kind == 1 ? PL(GH_name)   : PL(GC_name);
        case C_THANKS: return kind == 0 ? PL(GW_thanks) : kind == 1 ? PL(GH_thanks) : NOPOOL;
        case C_DEFAULT: return kind == 0 ? PL(GW_default) : kind == 1 ? PL(GH_default) : PL(GC_default);
        default: return NOPOOL;
    }
}

// ---------- konteks ped & balasan utama ----------
struct Ctx { float happy = 50, anger = 20, fear = 20; int trait = 0; /*0 friendly,1 grumpy,2 criminal,3 nervous,4 cocky*/
             std::string name; bool knows = false; int times = 0; std::vector<std::string> recent;
             int gang = 0, rel = 0; std::string pname = "homie"; };

inline int MoodVariant(const Ctx& c) { return c.anger > 60 ? 1 : c.fear > 60 ? 2 : c.happy > 65 ? 3 : 0; }
inline int ToneVariant(const Ctx& c) {                               // untuk hinaan/ancaman
    if (c.fear > 60 || c.trait == 3) return 0;
    if (c.trait == 4 || c.trait == 2 || c.anger > 60 || c.trait == 1) return 1;
    return 2;
}
inline std::string Fill(std::string s, const Ctx& c, const std::string& w = "") {
    for (size_t p; (p = s.find("{n}")) != std::string::npos; ) s.replace(p, 3, c.name);
    for (size_t p; (p = s.find("{p}")) != std::string::npos; ) s.replace(p, 3, c.pname);
    for (size_t p; (p = s.find("{g}")) != std::string::npos; ) s.replace(p, 3, GangName(c.gang));
    for (size_t p; (p = s.find("{c}")) != std::string::npos; ) s.replace(p, 3, GangColor(c.gang));
    for (size_t p; (p = s.find("{rv}")) != std::string::npos; ) s.replace(p, 4, GangRival(c.gang));
    for (size_t p; (p = s.find("{w}")) != std::string::npos; ) {
        std::string r = w.empty() ? std::string("that") : w;
        if (p == 0 && !r.empty() && (unsigned char)r[0] < 128) r[0] = (char)toupper((unsigned char)r[0]);
        s.replace(p, 3, r);
    }
    return s;
}
inline bool WasRecent(const Ctx& c, const std::string& s) {
    for (auto& r : c.recent) if (r == s) return true;
    return false;
}
inline std::string PickFresh(const Pool& p, const Ctx& c, std::mt19937& g, const std::string& w = "") {
    std::string s;
    for (int k = 0; k < 14; k++) { s = Fill(Pick(p, g), c, w); if (!WasRecent(c, s)) return s; }
    return s;
}


inline std::string AddTag(std::string s, int gang, std::mt19937& g) {   // tambah sebutan khas geng ("..., cuz.")
    Pool tp = GangTags(gang);
    if (tp.n == 0 || s.size() < 5) return s;
    std::string tag = Pick(tp, g);
    char last = s.back();
    if (last == '.' || last == '!' || last == '?') { s.pop_back(); return s + ", " + tag + last; }
    return s + ", " + tag;
}

inline bool shortMsg0(const std::string& s) { return s.size() < 6; }

inline std::string Reply(const Ctx& c, const std::string& said, int lang, std::mt19937& g, int& dH, int& dA, int& dF) {
    dH = dA = dF = 0;
    std::string t = NormText(said);
    std::string kw = Keyword(t);
    std::vector<int> cats = DetectAll(t);
    int first = -1, second = -1;
    for (int k : cats) { if (k == C_GREET && cats.size() > 1) continue; if (first < 0) first = k; else if (second < 0) second = k; }
    // perasaan player ("gua lagi sedih") -> respon empati, kecuali sedang ngancam/ngehina
    int feel = DetectFeel(t);
    if (feel >= 0 && first != C_THREAT && first != C_INSULT) {
        static const int dh[7] = {-2, -1, 6, -2, -2, 0, 0};
        dH = dh[feel];
        return PickFresh(FeelPool(lang, feel), c, g);
    }
    if (first < 0) first = DetectQuestionType(t);
    if (first < 0) first = said.find('?') != std::string::npos ? C_QUESTION : C_DEFAULT;
    int v = MoodVariant(c);
    switch (first) {
        case C_THREAT:  dF = 25; dA = 10; dH = -15; v = ToneVariant(c); break;
        case C_INSULT:  dA = 20; dH = -15; v = ToneVariant(c); break;
        case C_THANKS: case C_COMPLIMENT: dH = 12; dA = -8; break;
        case C_JOKE: dH = 6; dA = -4; break;
        case C_LOVE: dH = 5; break;
        case C_SORRY: dA = -12; dH = 4; break;
        case C_GREET: case C_NAME: case C_HOWARE: dH = 3; break;
        default: break;
    }
    if (first == C_STORY) {                                          // "ceritain dong" -> cerita acak
        std::string out = Fill(Compose(lang, g), c);
        if (g() % 3 == 0) out = PickFresh(PoolRandom(lang), c, g) + " " + out;
        return out;
    }
    if (shortMsg0(said)) kw.clear();
    if (first == C_LIKE && kw.empty()) first = C_QUESTION;           // butuh kata yang ditanya
    // ped anggota geng: sambutan hangat / dingin / permusuhan sesuai hubungan dengan geng player
    Pool gp = NOPOOL;
    if (c.gang) {
        unsigned P = c.rel >= 2 ? 75 : c.rel == 1 ? 55 : c.rel == 0 ? 40 : c.rel == -1 ? 60 : 75;
        int kind = c.rel >= 1 ? 0 : c.rel <= -2 ? 1 : c.rel == 0 ? 2 : (int)(g() % 2 ? 1 : 2);
        if (first == C_GANG) { if (lang == 0 && g() % 100 < 80) gp = PL(GANGTALK); }
        else if (first == C_INSULT) { if (c.rel <= -1 && lang == 0 && g() % 100 < 70) gp = PL(GH_insult); }
        else if (first == C_GREET || first == C_HOWARE || first == C_BYE || first == C_NAME || first == C_THANKS || first == C_DEFAULT) {
            if (g() % 100 < P) gp = GangPool(first, kind, lang);
        }
    }
    std::string out;
    bool shortMsg = said.size() < 6;                                  // "ok", "hmm", "bro": jawab singkat saja
    if (gp.n == 0 && !shortMsg && (first == C_DEFAULT || first == C_QUESTION || first == C_WHAT || first == C_WHO)) {
        unsigned r = g() % 100;
        if (!kw.empty() && r < 55) out = PickFresh(PoolEcho(lang), c, g, kw);      // ulang topik dari player supaya nyambung
        else if (r < 63) out = PickFresh(PoolRandom(lang), c, g);
        else if (r < 68) out = PickFresh(PoolAbsurd(lang), c, g);
        else if (r < 73) out = Fill(Compose(lang, g), c);
    }
    if (out.empty()) out = gp.n ? PickFresh(gp, c, g, kw) : PickFresh(GetPool(lang, first, v), c, g, kw);
    if (second >= 0 && second != first && second != C_LIKE && second != C_STORY && g() % 100 < 18) {   // kadang dua topik sekaligus
        int v2 = (second == C_THREAT || second == C_INSULT) ? ToneVariant(c) : MoodVariant(c);
        out += " " + PickFresh(GetPool(lang, second, v2), c, g, kw);
    }
    if (c.gang && g() % 100 < 35) out = AddTag(out, c.gang, g);
    return out;
}

// Ucapan spontan ped. kind: 0 sapaan, 1 olokan, 2 gumaman
inline std::string Spontaneous(const Ctx& c, int lang, int kind, std::mt19937& g) {
    if (kind == 1) {
        if (c.gang && c.rel >= 1) { Pool gp = GangPool(C_GREET, 0, lang); if (gp.n) return PickFresh(gp, c, g); }          // ke temen sendiri: sapaan, bukan hinaan
        if (c.gang && c.rel <= -1 && lang == 0) return PickFresh(PL(GH_insult), c, g);
        return PickFresh(PoolSpInsult(lang), c, g);
    }
    if (kind == 2) {
        unsigned r = g() % 100;
        if (r < 40) return PickFresh(PoolRandom(lang), c, g);
        if (r < 65) return PickFresh(PoolAbsurd(lang), c, g);
        if (r < 85) return Fill(Compose(lang, g), c);
        return PickFresh(PoolMumble(lang), c, g);
    }
    unsigned r = g() % 100;
    if (c.gang && r < 70) {                                           // anggota geng menyapa sesuai hubungan dengan player
        int kind = c.rel >= 1 ? 0 : c.rel <= -1 ? 1 : 2;
        Pool gp = GangPool(C_GREET, kind, lang);
        if (gp.n) { std::string o = PickFresh(gp, c, g); return g() % 100 < 35 ? AddTag(o, c.gang, g) : o; }
    }
    if (r < 25) return PickFresh(PoolSpGreet(lang), c, g);
    if (r < 40) return PickFresh(PoolRandom(lang), c, g);
    return PickFresh(GetPool(lang, C_GREET, MoodVariant(c)), c, g);
}

// ---------- jawaban atas perintah: 1 follow 2 stop 3 leave 4 dance 5 hands_up 6 wave 7 flee 8 fight ----------
POOL(IA_EN, "Sure,","Alright,","Okay,","Fine,","You got it,","Deal,","No problem,","Gladly,","Why not,","Say no more,","Roger that,","Aye aye,","Consider it done,","Easy,","Cool,")
POOL(IA_ID, "Oke,","Siap,","Yaudah,","Boleh,","Gas,","Beres,","Santai,","Sip,")
POOL(IA_ES, "Claro,","Vale,","Está bien,","Perfecto,","Hecho,","De acuerdo,")
POOL(IY_EN1, "lead the way.","I'm right behind you.","I'll tag along.","let's roll.","I'll follow you.","where are we going?")
POOL(IY_EN2, "I'll wait right here.","I'm not moving.","I'll stand here like a statue.","freezing now.","staying put.")
POOL(IY_EN3, "I'm out of here.","I'm gone.","I'll get lost.","leaving now.","you won't see me again. Probably.")
POOL(IY_EN4, "watch these moves!","let's boogie!","check this out!","here we go!","time to shine!")
POOL(IY_EN5, "hands up, see?","don't shoot!","they're up, they're up!","I surrender!","easy, easy!")
POOL(IY_EN6, "*waves* hey there!","*waves enthusiastically* hello!","*waves* look at me being friendly.")
POOL(IY_EN7, "I'm running!","running now, don't look back!","see ya!","legs, do your thing!")
POOL(IY_EN8, "bring it!","your funeral, pal.","let's go, tough guy.","I'll make it quick.")
POOL(IY_ID1, "gua ikut.","jalan aja, gua di belakang.","gua nemenin lu.","ayo berangkat.")
POOL(IY_ID2, "gua tunggu di sini.","gua diam.","gua nggak gerak.","gua jadi patung dulu.")
POOL(IY_ID3, "gua cabut.","gua pergi.","gua ilang sekarang.","nggak bakal liat gua lagi.")
POOL(IY_ID4, "liat gerakan gua!","ayo joget!","nih, tonton!","saatnya beraksi!")
POOL(IY_ID5, "tangan gua naik! Jangan tembak!","gua nyerah!","tenang, tenang!","ini tangan gua, liat!")
POOL(IY_ID6, "*melambai* halo semuanya!","*melambai semangat* hai!")
POOL(IY_ID7, "gua kabur!","gua lari nih!","kaki, jalan!")
POOL(IY_ID8, "sini lu!","lu yang minta!","ayo maju!")
POOL(IY_ES1, "te sigo.","guía el camino.","voy contigo.")
POOL(IY_ES2, "aquí espero.","no me muevo.","me quedo quieto.")
POOL(IY_ES3, "ya me voy.","me largo.","desaparezco.")
POOL(IY_ES4, "¡mira estos pasos!","¡a bailar!","¡aquí voy!")
POOL(IY_ES5, "¡manos arriba!","¡no dispares!","¡me rindo!")
POOL(IY_ES6, "*saluda* ¡hola!","*saluda con entusiasmo* ¡hola a todos!")
POOL(IY_ES7, "¡corro, corro!","¡me escapo!","¡piernas, no me fallen!")
POOL(IY_ES8, "¡ven aquí!","¡tú lo pediste!","¡vamos!")
POOL(IR_EN1, "Nah, I've got my own business.","Not a chance, pal.","Follow you? Follow your own advice.","I'm not a puppy.","Ask someone else.","No way. I just sat down.")
POOL(IR_EN2, "I'll go where I please.","You're not my boss.","Nope. Moving.","Make me. Kidding. Don't.")
POOL(IR_EN4, "I'm not a dancer, buddy.","I've got two left feet.","Not in public. Not sober.","Find a DJ.")
POOL(IR_EN5, "You're not a cop. Forget it.","Hands up? You first.","I don't take orders from strangers.","Nice try.")
POOL(IR_EN8, "Whoa, I'm not fighting you, man.","Violence is never the answer. Unless it's pizza.","I'm a lover, not a fighter.","No thanks. I just got a haircut.")
POOL(IR_ID1, "Ogah, gua punya urusan sendiri.","Nggak mau, bro.","Emang gua anak anjing?","Tanya orang lain aja.")
POOL(IR_ID2, "Gua jalan ke mana gua mau.","Lu bukan bos gua.","Nggak. Gua jalan.")
POOL(IR_ID4, "Gua bukan penari, bro.","Kaki gua dua-duanya kiri.","Nggak di depan umum.")
POOL(IR_ID5, "Lu bukan polisi. Lupain aja.","Lu duluan yang angkat tangan.","Gua nggak terima perintah dari orang asing.")
POOL(IR_ID8, "Gua nggak mau berantem sama lu.","Kekerasan bukan jawaban.","Gua petani cinta, bukan petarung.")
POOL(IR_ES1, "No, tengo mis asuntos.","Ni lo sueñes.","Pregúntale a otro.")
POOL(IR_ES2, "Voy a donde quiera.","Tú no eres mi jefe.")
POOL(IR_ES4, "No soy bailarín.","Tengo dos pies izquierdos.")
POOL(IR_ES5, "No eres policía. Olvídalo.","Tú primero.")
POOL(IR_ES8, "No quiero pelear.","La violencia no es la respuesta.")

inline std::string IntentLine(int in, bool ok, int lang, std::mt19937& g) {
    Pool p = NOPOOL;
    if (ok) {
        Pool ack = lang == 1 ? PL(IA_ID) : lang == 2 ? PL(IA_ES) : PL(IA_EN);
        switch (in) {
            case 1: p = lang == 1 ? PL(IY_ID1) : lang == 2 ? PL(IY_ES1) : PL(IY_EN1); break;
            case 2: p = lang == 1 ? PL(IY_ID2) : lang == 2 ? PL(IY_ES2) : PL(IY_EN2); break;
            case 3: p = lang == 1 ? PL(IY_ID3) : lang == 2 ? PL(IY_ES3) : PL(IY_EN3); break;
            case 4: p = lang == 1 ? PL(IY_ID4) : lang == 2 ? PL(IY_ES4) : PL(IY_EN4); break;
            case 5: p = lang == 1 ? PL(IY_ID5) : lang == 2 ? PL(IY_ES5) : PL(IY_EN5); break;
            case 6: p = lang == 1 ? PL(IY_ID6) : lang == 2 ? PL(IY_ES6) : PL(IY_EN6); break;
            case 7: p = lang == 1 ? PL(IY_ID7) : lang == 2 ? PL(IY_ES7) : PL(IY_EN7); break;
            default: p = lang == 1 ? PL(IY_ID8) : lang == 2 ? PL(IY_ES8) : PL(IY_EN8); break;
        }
        std::string line = Pick(p, g);
        if (line[0] == '*') return line;                               // gerakan (melambai) tanpa awalan
        return std::string(Pick(ack, g)) + " " + line;
    }
    switch (in) {
        case 1: p = lang == 1 ? PL(IR_ID1) : lang == 2 ? PL(IR_ES1) : PL(IR_EN1); break;
        case 2: p = lang == 1 ? PL(IR_ID2) : lang == 2 ? PL(IR_ES2) : PL(IR_EN2); break;
        case 4: p = lang == 1 ? PL(IR_ID4) : lang == 2 ? PL(IR_ES4) : PL(IR_EN4); break;
        case 5: p = lang == 1 ? PL(IR_ID5) : lang == 2 ? PL(IR_ES5) : PL(IR_EN5); break;
        default: p = lang == 1 ? PL(IR_ID8) : lang == 2 ? PL(IR_ES8) : PL(IR_EN8); break;
    }
    return Pick(p, g);
}

// ---------- gender model skin GTA SA (ID skin cewek) ----------
inline int GenderOfSkin(int m) {                                       // 1 cowok, 2 cewek, 0 tidak diketahui
    static const int F[] = {9,10,11,12,13,31,38,39,40,41,53,54,55,56,63,64,65,69,75,76,77,85,87,88,89,90,91,92,93,129,130,131,138,139,140,141,145,148,150,151,152,157,169,178,190,191,192,193,194,195,196,197,198,199,201,205,207,211,214,215,216,219,224,225,226,231,232,233,237,238,243,244,245,246,251,256,257,263,298};
    if (m < 0 || m > 312) return 0;
    for (int f : F) if (f == m) return 2;
    return 1;
}
inline const char* NameFor(int gender, std::mt19937& g) {
    if (gender == 2) return PickA(FEMALE_NAMES, sizeof(FEMALE_NAMES) / sizeof(FEMALE_NAMES[0]), g);
    if (gender == 1) return PickA(MALE_NAMES, sizeof(MALE_NAMES) / sizeof(MALE_NAMES[0]), g);
    return PickA(UNISEX_NAMES, sizeof(UNISEX_NAMES) / sizeof(UNISEX_NAMES[0]), g);
}

} // namespace Vocab
