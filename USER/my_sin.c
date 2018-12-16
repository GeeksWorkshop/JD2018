/*
**************************************************************************************************************
*	@file	my_sin.c
*	@author  
*	@version 
*	@date    
*	@brief	���Ǻ������
***************************************************************************************************************
*/

/*
 *	ͷ�ļ�
 */
#include "my_sin.h"
#include <string.h>

/*
 *	sin������
 */
static const float sin_table[901] = {	0					,	0.001745328365898	,	0.003490651415223	,	0.005235963831419	,	0.006981260297961	,	0.008726535498373	,	0.010471784116245	,	0.012217000835247	,	0.013962180339145	,	0.015707317311820	,	
										0.017452406437283	,	0.019197442399689	,	0.020942419883357	,	0.022687333572781	,	0.024432178152653	,	0.026176948307873	,	0.027921638723568	,	0.029666244085110	,	0.031410759078128	,	0.033155178388526	,	
										0.034899496702501	,	0.036643708706556	,	0.038387809087519	,	0.040131792532559	,	0.041875653729199	,	0.043619387365336	,	0.045362988129253	,	0.047106450709642	,	0.048849769795613	,	0.050592940076713	,	
										0.052335956242943	,	0.054078812984775	,	0.055821504993163	,	0.057564026959567	,	0.059306373575961	,	0.061048539534856	,	0.062790519529313	,	0.064532308252958	,	0.066273900400000	,	0.068015290665248	,	
										0.069756473744125	,	0.071497444332685	,	0.073238197127631	,	0.074978726826327	,	0.076719028126818	,	0.078459095727844	,	0.080198924328858	,	0.081938508630040	,	0.083677843332315	,	0.085416923137367	,	
										0.087155742747658	,	0.088894296866441	,	0.090632580197780	,	0.092370587446561	,	0.094108313318514	,	0.095845752520224	,	0.097582899759149	,	0.099319749743639	,	0.101056297182946	,	0.102792536787247	,	
										0.104528463267653	,	0.106264071336233	,	0.107999355706023	,	0.109734311091045	,	0.111468932206325	,	0.113203213767907	,	0.114937150492867	,	0.116670737099333	,	0.118403968306501	,	0.120136838834647	,	
										0.121869343405147	,	0.123601476740493	,	0.125333233564304	,	0.127064608601351	,	0.128795596577563	,	0.130526192220052	,	0.132256390257122	,	0.133986185418292	,	0.135715572434304	,	0.137444546037147	,	
										0.139173100960065	,	0.140901231937583	,	0.142628933705512	,	0.144356201000973	,	0.146083028562412	,	0.147809411129611	,	0.149535343443710	,	0.151260820247219	,	0.152985836284038	,	0.154710386299468	,
										0.156434465040231	,	0.158158067254484	,	0.159881187691835	,	0.161603821103361	,	0.163325962241622	,	0.165047605860678	,	0.166768746716102	,	0.168489379565003	,	0.170209499166033	,	0.171929100279410	,	
										0.173648177666930	,	0.175366726091987	,	0.177084740319583	,	0.178802215116350	,	0.180519145250560	,	0.182235525492147	,	0.183951350612720	,	0.185666615385577	,	0.187381314585725	,	0.189095442989891	,	
										0.190808995376545	,	0.192521966525907	,	0.194234351219972	,	0.195946144242518	,	0.197657340379126	,	0.199367934417197	,	0.201077921145965	,	0.202787295356513	,	0.204496051841790	,	0.206204185396630	,	
										0.207911690817759	,	0.209618562903822	,	0.211324796455389	,	0.213030386274977	,	0.214735327167063	,	0.216439613938103	,	0.218143241396543	,	0.219846204352838	,	0.221548497619467	,	0.223250116010951	,	
										0.224951054343865	,	0.226651307436855	,	0.228350870110656	,	0.230049737188104	,	0.231747903494157	,	0.233445363855905	,	0.235142113102590	,	0.236838146065619	,	0.238533457578581	,	0.240228042477264	,	
										0.241921895599668	,	0.243615011786023	,	0.245307385878803	,	0.246999012722743	,	0.248689887164855	,	0.250380004054441	,	0.252069358243114	,	0.253757944584806	,	0.255445757935791	,	0.257132793154696	,	
										0.258819045102521	,	0.260504508642648	,	0.262189178640865	,	0.263873049965373	,	0.265556117486809	,	0.267238376078257	,	0.268919820615266	,	0.270600445975864	,	0.272280247040574	,	0.273959218692432	,	
										0.275637355816999	,	0.277314653302378	,	0.278991106039229	,	0.280666708920788	,	0.282341456842877	,	0.284015344703923	,	0.285688367404974	,	0.287360519849712	,	0.289031796944472	,	0.290702193598253	,	
										0.292371704722737	,	0.294040325232304	,	0.295708050044047	,	0.297374874077786	,	0.299040792256087	,	0.300705799504273	,	0.302369890750444	,	0.304033060925490	,	0.305695304963106	,	0.307356617799807	,		
										0.309016994374947	,	0.310676429630732	,	0.312334918512233	,	0.313992455967405	,	0.315649036947102	,	0.317304656405092	,	0.318959309298070	,	0.320612990585676	,	0.322265695230511	,	0.323917418198149	,	
										0.325568154457157	,	0.327217898979104	,	0.328866646738583	,	0.330514392713223	,	0.332161131883703	,	0.333806859233771	,	0.335451569750255	,	0.337095258423082	,	0.338737920245291	,	0.340379550213050	,	
										0.342020143325669	,	0.343659694585616	,	0.345298198998535	,	0.346935651573256	,	0.348572047321815	,	0.350207381259467	,	0.351841648404702	,	0.353474843779257	,	0.355106962408137	,	0.356737999319625	,	
										0.358367949545300	,	0.359996808120051	,	0.361624570082092	,	0.363251230472978	,	0.364876784337620	,	0.366501226724297	,	0.368124552684678	,	0.369746757273829	,	0.371367835550235	,	0.372987782575809	,	
										0.374606593415912	,	0.376224263139366	,	0.377840786818467	,	0.379456159529005	,	0.381070376350274	,	0.382683432365090	,	0.384295322659804	,	0.385906042324319	,	0.387515586452103	,	0.389123950140206	,	
										0.390731128489274	,	0.392337116603562	,	0.393941909590951	,	0.395545502562965	,	0.397147890634781	,	0.398749068925246	,	0.400349032556895	,	0.401947776655960	,	0.403545296352390	,	0.405141586779863	,	
										0.406736643075800	,	0.408330460381385	,	0.409923033841573	,	0.411514358605109	,	0.413104429824542	,	0.414693242656239	,	0.416280792260401	,	0.417867073801077	,	0.419452082446177	,	0.421035813367491	,	
										0.422618261740699	,	0.424199422745390	,	0.425779291565073	,	0.427357863387192	,	0.428935133403146	,	0.430511096808295	,	0.432085748801982	,	0.433659084587544	,	0.435231099372328	,	0.436801788367702	,
										0.438371146789077	,	0.439939169855915	,	0.441505852791745	,	0.443071190824180	,	0.444635179184927	,	0.446197813109809	,	0.447759087838770	,	0.449318998615897	,	0.450877540689431	,	0.452434709311783	,	
										0.453990499739547	,	0.455544907233516	,	0.457097927058694	,	0.458649554484315	,	0.460199784783852	,	0.461748613235034	,	0.463296035119862	,	0.464842045724620	,	0.466386640339891	,	0.467929814260573	,	
										0.469471562785891	,	0.471011881219410	,	0.472550764869054	,	0.474088209047116	,	0.475624209070275	,	0.477158760259608	,	0.478691857940607	,	0.480223497443189	,	0.481753674101715	,	0.483282383255002	,	
										0.484809620246337	,	0.486335380423491	,	0.487859659138733	,	0.489382451748846	,	0.490903753615141	,	0.492423560103467	,	0.493941866584231	,	0.495458668432408	,	0.496973961027555	,	0.498487739753830	,	
										0.500000000000000	,	0.501510737159457	,	0.503019946630235	,	0.504527623815019	,	0.506033764121164	,	0.507538362960704	,	0.509041415750371	,	0.510542917911606	,	0.512042864870572	,	0.513541252058170	,	
										0.515038074910054	,	0.516533328866642	,	0.518027009373130	,	0.519519111879509	,	0.521009631840576	,	0.522498564715949	,	0.523985905970079	,	0.525471651072268	,	0.526955795496678	,	0.528438334722347	,	
										0.529919264233205	,	0.531398579518083	,	0.532876276070730	,	0.534352349389826	,	0.535826794978997	,	0.537299608346824	,	0.538770785006863	,	0.540240320477655	,	0.541708210282740	,	0.543174449950671	,	
										0.544639035015027	,	0.546101961014429	,	0.547563223492550	,	0.549022817998132	,	0.550480740084996	,	0.551936985312058	,	0.553391549243344	,	0.554844427447999	,	0.556295615500305	,	0.557745108979690	,	
										0.559192903470747	,	0.560638994563242	,	0.562083377852131	,	0.563526048937572	,	0.564967003424938	,	0.566406236924833	,	0.567843745053101	,	0.569279523430844	,	0.570713567684432	,	0.572145873445516	,	
										0.573576436351046	,	0.575005252043279	,	0.576432316169793	,	0.577857624383505	,	0.579281172342679	,	0.580702955710940	,	0.582122970157289	,	0.583541211356118	,	0.584957674987216	,	0.586372356735789	,	
										0.587785252292473	,	0.589196357353342	,	0.590605667619925	,	0.592013178799220	,	0.593418886603702	,	0.594822786751341	,	0.596224874965616	,	0.597625146975521	,	0.599023598515586	,	0.600420225325884	,	
										0.601815023152048	,	0.603207987745283	,	0.604599114862375	,	0.605988400265711	,	0.607375839723287	,	0.608761429008721	,	0.610145163901268	,	0.611527040185831	,	0.612907053652977	,	0.614285200098943	,	
										0.615661475325658	,	0.617035875140749	,	0.618408395357554	,	0.619779031795140	,	0.621147780278311	,	0.622514636637620	,	0.623879596709386	,	0.625242656335705	,	0.626603811364461	,	0.627963057649338	,	
										0.629320391049838	,	0.630675807431286	,	0.632029302664851	,	0.633380872627550	,	0.634730513202268	,	0.636078220277764	,	0.637423989748690	,	0.638767817515598	,	0.640109699484956	,	0.641449631569158	,	
										0.642787609686539	,	0.644123629761387	,	0.645457687723951	,	0.646789779510460	,	0.648119901063131	,	0.649448048330184	,	0.650774217265851	,	0.652098403830392	,	0.653420603990105	,	0.654740813717340	,	
										0.656059028990507	,	0.657375245794096	,	0.658689460118681	,	0.660001667960937	,	0.661311865323652	,	0.662620048215738	,	0.663926212652242	,	0.665230354654361	,	0.666532470249453	,	0.667832555471047	,	
										0.669130606358858	,	0.670426618958799	,	0.671720589322990	,	0.673012513509773	,	0.674302387583723	,	0.675590207615660	,	0.676875969682661	,	0.678159669868071	,	0.679441304261517	,	0.680720868958918	,
										0.681998360062499	,	0.683273773680799	,	0.684547105928689	,	0.685818352927376	,	0.687087510804423	,	0.688354575693754	,	0.689619543735670	,	0.690882411076858	,	0.692143173870407	,	0.693401828275813	,	
										0.694658370458997	,	0.695912796592314	,	0.697165102854565	,	0.698415285431006	,	0.699663340513365	,	0.700909264299851	,	0.702153052995162	,	0.703394702810504	,	0.704634209963595	,	0.705871570678681	,	
										0.707106781186548	,	0.708339837724529	,	0.709570736536521	,	0.710799473872992	,	0.712026045990997	,	0.713250449154182	,	0.714472679632803	,	0.715692733703736	,	0.716910607650483	,	0.718126297763189	,	
										0.719339800338651	,	0.720551111680330	,	0.721760228098362	,	0.722967145909568	,	0.724171861437468	,	0.725374371012288	,	0.726574670970976	,	0.727772757657210	,	0.728968627421412	,	0.730162276620752	,	
										0.731353701619171	,	0.732542898787379	,	0.733729864502876	,	0.734914595149960	,	0.736097087119734	,	0.737277336810124	,	0.738455340625884	,	0.739631094978610	,	0.740804596286750	,	0.741975840975616	,	
										0.743144825477394	,	0.744311546231154	,	0.745475999682862	,	0.746638182285391	,	0.747798090498532	,	0.748955720789002	,	0.750111069630459	,	0.751264133503511	,	0.752414908895724	,	0.753563392301638	,	
										0.754709580222772	,	0.755853469167640	,	0.756995055651756	,	0.758134336197652	,	0.759271307334881	,	0.760405965600031	,	0.761538307536737	,	0.762668329695688	,	0.763796028634642	,	0.764921400918432	,	
										0.766044443118978	,	0.767165151815300	,	0.768283523593523	,	0.769399555046895	,	0.770513242775789	,	0.771624583387720	,	0.772733573497351	,	0.773840209726506	,	0.774944488704180	,	0.776046407066546	,	
										0.777145961456971	,	0.778243148526021	,	0.779337964931474	,	0.780430407338330	,	0.781520472418819	,	0.782608156852414	,	0.783693457325840	,	0.784776370533083	,	0.785856893175402	,	0.786935021961337	,	
										0.788010753606722	,	0.789084084834691	,	0.790155012375690	,	0.791223532967490	,	0.792289643355191	,	0.793353340291235	,	0.794414620535418	,	0.795473480854896	,	0.796529918024196	,	0.797583928825228	,	
										0.798635510047293	,	0.799684658487091	,	0.800731370948733	,	0.801775644243754	,	0.802817475191115	,	0.803856860617217	,	0.804893797355914	,	0.805928282248516	,	0.806960312143802	,	0.807989883898031	,	
										0.809016994374948	,	0.810041640445796	,	0.811063818989327	,	0.812083526891806	,	0.813100761047028	,	0.814115518356319	,	0.815127795728554	,	0.816137590080160	,	0.817144898335129	,	0.818149717425023	,	
										0.819152044288992	,	0.820151875873772	,	0.821149209133704	,	0.822144041030738	,	0.823136368534442	,	0.824126188622016	,	0.825113498278295	,	0.826098294495764	,	0.827080574274562	,	0.828060334622494	,	
										0.829037572555042	,	0.830012285095367	,	0.830984469274328	,	0.831954122130483	,	0.832921240710100	,	0.833885822067168	,	0.834847863263407	,	0.835807361368270	,	0.836764313458962	,	0.837718716620439	,	
										0.838670567945424	,	0.839619864534413	,	0.840566603495684	,	0.841510781945306	,	0.842452397007148	,	0.843391445812886	,	0.844327925502015	,	0.845261833221856	,	0.846193166127564	,	0.847121921382137	,	
										0.848048096156426	,	0.848971687629141	,	0.849892692986864	,	0.850811109424051	,	0.851726934143048	,	0.852640164354092	,	0.853550797275327	,	0.854458830132807	,	0.855364260160507	,	0.856267084600328	,	
										0.857167300702112	,	0.858064905723645	,	0.858959896930664	,	0.859852271596873	,	0.860742027003944	,	0.861629160441526	,	0.862513669207257	,	0.863395550606772	,	0.864274801953705	,	0.865151420569705	,
										0.866025403784439	,	0.866896748935603	,	0.867765453368928	,	0.868631514438191	,	0.869494929505219	,	0.870355695939900	,	0.871213811120189	,	0.872069272432121	,	0.872922077269810	,	0.873772223035465	,	
										0.874619707139396	,	0.875464527000018	,	0.876306680043864	,	0.877146163705589	,	0.877982975427981	,	0.878817112661965	,	0.879648572866617	,	0.880477353509162	,	0.881303452064992	,	0.882126866017668	,	
										0.882947592858927	,	0.883765630088693	,	0.884580975215084	,	0.885393625754416	,	0.886203579231215	,	0.887010833178222	,	0.887815385136401	,	0.888617232654949	,	0.889416373291298	,	0.890212804611127	,	
										0.891006524188368	,	0.891797529605214	,	0.892585818452126	,	0.893371388327838	,	0.894154236839368	,	0.894934361602025	,	0.895711760239413	,	0.896486430383441	,	0.897258369674328	,	0.898027575760616	,	
										0.898794046299167	,	0.899557778955180	,	0.900318771402194	,	0.901077021322092	,	0.901832526405114	,	0.902585284349861	,	0.903335292863301	,	0.904082549660778	,	0.904827052466020	,	0.905568799011140	,	
										0.906307787036650	,	0.907044014291465	,	0.907777478532909	,	0.908508177526722	,	0.909236109047069	,	0.909961270876543	,	0.910683660806177	,	0.911403276635445	,	0.912120116172273	,	0.912834177233043	,	
										0.913545457642601	,	0.914253955234264	,	0.914959667849825	,	0.915662593339561	,	0.916362729562240	,	0.917060074385124	,	0.917754625683981	,	0.918446381343087	,	0.919135339255235	,	0.919821497321738	,	
										0.920504853452440	,	0.921185405565721	,	0.921863151588501	,	0.922538089456246	,	0.923210217112981	,	0.923879532511287	,	0.924546033612313	,	0.925209718385782	,	0.925870584809995	,	0.926528630871837	,	
										0.927183854566787	,	0.927836253898920	,	0.928485826880914	,	0.929132571534056	,	0.929776485888251	,	0.930417567982025	,	0.931055815862528	,	0.931691227585549	,	0.932323801215512	,	0.932953534825489	,
										0.933580426497202	,	0.934204474321029	,	0.934825676396014	,	0.935444030829867	,	0.936059535738973	,	0.936672189248398	,	0.937281989491892	,	0.937888934611898	,	0.938493022759556	,	0.939094252094709	,	
										0.939692620785908	,	0.940288127010419	,	0.940880768954226	,	0.941470544812038	,	0.942057452787297	,	0.942641491092178	,	0.943222657947601	,	0.943800951583229	,	0.944376370237481	,	0.944948912157531	,	
										0.945518575599317	,	0.946085358827545	,	0.946649260115696	,	0.947210277746029	,	0.947768410009586	,	0.948323655206199	,	0.948876011644496	,	0.949425477641904	,	0.949972051524653	,	0.950515731627784	,	
										0.951056516295154	,	0.951594403879438	,	0.952129392742139	,	0.952661481253586	,	0.953190667792947	,	0.953716950748227	,	0.954240328516277	,	0.954760799502798	,	0.955278362122344	,	0.955793014798330	,	
										0.956304755963035	,	0.956813584057607	,	0.957319497532067	,	0.957822494845315	,	0.958322574465133	,	0.958819734868193	,	0.959313974540057	,	0.959805291975187	,	0.960293685676943	,	0.960779154157594	,	
										0.961261695938319	,	0.961741309549211	,	0.962217993529285	,	0.962691746426479	,	0.963162566797658	,	0.963630453208623	,	0.964095404234110	,	0.964557418457798	,	0.965016494472311	,	0.965472630879225	,	
										0.965925826289068	,	0.966376079321329	,	0.966823388604459	,	0.967267752775877	,	0.967709170481971	,	0.968147640378108	,	0.968583161128631	,	0.969015731406870	,	0.969445349895139	,	0.969872015284747	,	
										0.970295726275997	,	0.970716481578191	,	0.971134279909636	,	0.971549119997646	,	0.971961000578546	,	0.972369920397677	,	0.972775878209397	,	0.973178872777088	,	0.973578902873160	,	0.973975967279052	,
										0.974370064785235	,	0.974761194191222	,	0.975149354305563	,	0.975534543945857	,	0.975916761938747	,	0.976296007119933	,	0.976672278334168	,	0.977045574435264	,	0.977415894286096	,	0.977783236758606	,	
										0.978147600733806	,	0.978508985101778	,	0.978867388761685	,	0.979222810621766	,	0.979575249599344	,	0.979924704620830	,	0.980271174621722	,	0.980614658546613	,	0.980955155349192	,	0.981292663992245	,	
										0.981627183447664	,	0.981958712696444	,	0.982287250728689	,	0.982612796543615	,	0.982935349149554	,	0.983254907563955	,	0.983571470813386	,	0.983885037933542	,	0.984195607969242	,	0.984503179974437	,	
										0.984807753012208	,	0.985109326154774	,	0.985407898483490	,	0.985703469088854	,	0.985996037070505	,	0.986285601537231	,	0.986572161606969	,	0.986855716406807	,	0.987136265072988	,	0.987413806750911	,	
										0.987688340595138	,	0.987959865769389	,	0.988228381446553	,	0.988493886808684	,	0.988756381047006	,	0.989015863361917	,	0.989272332962988	,	0.989525789068970	,	0.989776230907789	,	0.990023657716558	,	
										0.990268068741570	,	0.990509463238309	,	0.990747840471444	,	0.990983199714836	,	0.991215540251542	,	0.991444861373810	,	0.991671162383090	,	0.991894442590030	,	0.992114701314478	,	0.992331937885489	,	
										0.992546151641322	,	0.992757341929446	,	0.992965508106537	,	0.993170649538486	,	0.993372765600396	,	0.993571855676588	,	0.993767919160596	,	0.993960955455180	,	0.994150963972315	,	0.994337944133205	,	
										0.994521895368273	,	0.994702817117174	,	0.994880708828788	,	0.995055569961226	,	0.995227399981831	,	0.995396198367179	,	0.995561964603080	,	0.995724698184582	,	0.995884398615970	,	0.996041065410770	,	
										0.996194698091746	,	0.996345296190906	,	0.996492859249504	,	0.996637386818037	,	0.996778878456247	,	0.996917333733128	,	0.997052752226920	,	0.997185133525116	,	0.997314477224458	,	0.997440782930944	,
										0.997564050259824	,	0.997684278835605	,	0.997801468292050	,	0.997915618272179	,	0.998026728428272	,	0.998134798421867	,	0.998239827923765	,	0.998341816614028	,	0.998440764181981	,	0.998536670326212	,	
										0.998629534754574	,	0.998719357184186	,	0.998806137341434	,	0.998889874961970	,	0.998970569790715	,	0.999048221581858	,	0.999122830098858	,	0.999194395114446	,	0.999262916410621	,	0.999328393778656	,	
										0.999390827019096	,	0.999450215941757	,	0.999506560365732	,	0.999559860119384	,	0.999610115040354	,	0.999657324975557	,	0.999701489781183	,	0.999742609322698	,	0.999780683474846	,	0.999815712121644	,	
										0.999847695156391	,	0.999876632481661	,	0.999902524009304	,	0.999925369660452	,	0.999945169365512	,	0.999961923064171	,	0.999975630705395	,	0.999986292247427	,	0.999993907657790	,	0.999998476913288	,	
										1
									};

/*
 *	my_sin:	sin�������
 *	ang:	�Ƕȣ���λ�㣩
 */
extern float my_sin(float ang)
{
	int32_t alpha = ang * 10; 	/*�Ƕ�ϸ��Ϊ0.1��*/

	while (alpha<0)
		alpha += 3600;
	while (alpha>3600)
		alpha -= 3600;			/*���Ƕ�ת����0--360��֮��*/

	if (alpha<=900)
		return  sin_table[alpha];
	else if (alpha<=1800)
		return  sin_table[1800-alpha];
	else if (alpha<=2700)
		return -sin_table[alpha-1800];
	else 
		return -sin_table[3600-alpha];
}